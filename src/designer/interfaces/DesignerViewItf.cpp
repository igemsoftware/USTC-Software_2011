#include "DesignerViewItf.h"

#include "DesignerMainWnd.h"

#include "common/utils/itemregistry/ItemRegistry.h"

DesignerViewItf* DesignerViewItf::createView
        (QString viewName, DesignerMainWnd* mainWnd)
{
    ViewItfRegistryItem metaObj = ViewItfRegistry::find(viewName);
    if(metaObj.metaObject.className()==viewName)
        return dynamic_cast<DesignerViewItf*>(metaObj.metaObject.newInstance(Q_ARG(DesignerMainWnd*, mainWnd)));

    return NULL;
}

QString DesignerViewItf::getViewTitleByName(QString viewName)
{

    ViewItfRegistryItem metaObj = ViewItfRegistry::find(viewName);
    if(metaObj.metaObject.className()==viewName)
        return metaObj.viewTitle;

    return viewName;
}


QMetaObject DesignerViewItf::getViewMetaObjectByName(QString viewName)
{
    return ViewItfRegistry::find(viewName).metaObject;
}
