#include "DesignerViewItf.h"

#include "DesignerMainWnd.h"

#include "views/welcomeview/WelcomeView.h"
#include "views/filedescriptionview/FileDescriptionView.h"

#include "views/assemblyview/AssemblyView.h"

#include "views/networkview/NetworkView.h"
#include "views/sbmleditorview/SBMLEditorView.h"

#include "views/behaviorview/BehaviorView.h"
#include "views/plot3dview/Plot3DView.h"
#include "views/partview/PartView.h"
#include "views/odeview/ODEView.h"

#include "views/aboutview/AboutView.h"

#include "views/clothodbview/ClothoDBView.h"



static QMetaObject metaObjectsOfViews[] = {
    AssemblyView::staticMetaObject,
    NetworkView::staticMetaObject,
    BehaviorView::staticMetaObject,
    SBMLEditorView::staticMetaObject,
    WelcomeView::staticMetaObject,
    FileDescriptionView::staticMetaObject,
    PartView::staticMetaObject,
    Plot3DView::staticMetaObject,
    ODEView::staticMetaObject,
    AboutView::staticMetaObject,
    ClothoDBView::staticMetaObject,
};

static QString     titlesOfViews[] = {
    QObject::tr("Assembly View"),
    QObject::tr("Network View"),
    QObject::tr("Behavior View"),
    QObject::tr("SBML Editor View"),
    QObject::tr("Welcome"),
    QObject::tr("Views"),
    QObject::tr("Part View"),
    QObject::tr("Plot3D View"),
    QObject::tr("ODE View"),
    QObject::tr("About"),
    QObject::tr("Clotho Data Source")
};

DesignerViewItf* DesignerViewItf::createView
        (QString viewName, DesignerMainWnd* mainWnd)
{
    for(size_t i = 0 ; i < (sizeof(metaObjectsOfViews)/sizeof(metaObjectsOfViews[0])); i++ )
    {
        if(viewName==metaObjectsOfViews[i].className())
        {
            return dynamic_cast<DesignerViewItf*>(metaObjectsOfViews[i].newInstance(Q_ARG(DesignerMainWnd*, mainWnd)));
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


//! \bug Not tested~
QMetaObject DesignerViewItf::getViewMetaObjectByName(QString name)
{
    for(size_t i = 0 ; i < (sizeof(metaObjectsOfViews)/sizeof(metaObjectsOfViews[0])); i++ )
    {
        if(name==metaObjectsOfViews[i].className())
        {
            return metaObjectsOfViews[i];
        }
    }
    return DesignerViewItf::staticMetaObject;
}
