#include "DesignerViewItf.h"

#include "DesignerAssemblyView.h"
#include "DesignerNetworkView.h"
#include "DesignerBehaviorView.h"

static QMetaObject metaObjectsOfViews[] = {
    AssemblyView::staticMetaObject,
    NetworkView::staticMetaObject,
    BehaviorView::staticMetaObject,
};

DesignerViewItf* DesignerViewItf::createView
        (QString& viewName, QWidget* centralWidget)
{
    for(size_t i = 0 ; i < (sizeof(metaObjectsOfViews)/sizeof(metaObjectsOfViews[0])); i++ )
    {
        if(viewName==metaObjectsOfViews[i].className())
        {
            return dynamic_cast<DesignerViewItf*>(metaObjectsOfViews[i].newInstance(Q_ARG(QWidget*, centralWidget)));
        }
    }
    return NULL;
}
