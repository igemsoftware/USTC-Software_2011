#include "DesignerViewItf.h"

#include "DesignerMainWnd.h"

#include "views/welcomeview/WelcomeView.h"

#include "views/assemblyview/DesignerAssemblyView.h"
#include "views/networkview/DesignerNetworkView.h"
#include "views/behaviorview/DesignerBehaviorView.h"

static QMetaObject metaObjectsOfViews[] = {
    AssemblyView::staticMetaObject,
    NetworkView::staticMetaObject,
    BehaviorView::staticMetaObject,
    WelcomeView::staticMetaObject,
};

static QString     titlesOfViews[] = {
    QObject::tr("Assembly View"),
    QObject::tr("Network View"),
    QObject::tr("Behavior View"),
    QObject::tr("Welcome")
};

DesignerViewItf* DesignerViewItf::createView
        (QString viewName, QWidget* centralWidget, DesignerMainWnd* mainWnd)
{
    for(size_t i = 0 ; i < (sizeof(metaObjectsOfViews)/sizeof(metaObjectsOfViews[0])); i++ )
    {
        if(viewName==metaObjectsOfViews[i].className())
        {
            return dynamic_cast<DesignerViewItf*>(metaObjectsOfViews[i].newInstance(Q_ARG(QWidget*, centralWidget), Q_ARG(DesignerMainWnd*, mainWnd)));
        }
    }
    return NULL;
}

QString DesignerViewItf::getViewTitleByName(QString name)
{
    for(size_t i = 0 ; i < (sizeof(metaObjectsOfViews)/sizeof(metaObjectsOfViews[0])); i++ )
    {
        if(name==metaObjectsOfViews[i].className())
        {
            return titlesOfViews[i];
        }
    }
    return name;
}

QString DesignerViewItf::getViewTitleByIndex(int index)
{
    if(index>=0 && index < (int)(sizeof(metaObjectsOfViews)/sizeof(metaObjectsOfViews[0])))
        return titlesOfViews[index];
    return "";
}
