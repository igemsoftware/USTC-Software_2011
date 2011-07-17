#include "DesignerMainWnd.h"

#include "common/utils/itemregistry/ItemRegistry.h"
#include "DesignerViewItf.h"

#include "views/aboutview/AboutView.h"
#include "views/assemblyview/AssemblyView.h"
#include "views/behaviorview/BehaviorView.h"
#include "views/clothodbview/ClothoDBView.h"
#include "views/filedescriptionview/FileDescriptionView.h"
#include "views/networkview/NetworkView.h"
#include "views/odeview/ODEView.h"
#include "views/partview/PartView.h"
#include "views/plot3dview/Plot3DView.h"
#include "views/sbmleditorview/SBMLEditorView.h"
#include "views/welcomeview/WelcomeView.h"

void DesignerViewItf::initializeIfNotYet()
{
    static bool initialized = false;
    if(!initialized)
    {
        initialized = true;
        LACHESIS_DECLARE_VIEW(AboutView, "About");
        LACHESIS_DECLARE_VIEW(AssemblyView, "Assembly View");
        LACHESIS_DECLARE_VIEW(BehaviorView, "Behavior View");
        LACHESIS_DECLARE_VIEW(ClothoDBView, "Clotho Data Source");
        LACHESIS_DECLARE_VIEW(FileDescriptionView, "Views");
        LACHESIS_DECLARE_VIEW(NetworkView, "Network View");
        LACHESIS_DECLARE_VIEW(ODEView, "ODE View");
        LACHESIS_DECLARE_VIEW(PartView, "Part View");
        LACHESIS_DECLARE_VIEW(Plot3DView, "Plot3D View");
        LACHESIS_DECLARE_VIEW(SBMLEditorView, "SBML Editor View");
        LACHESIS_DECLARE_VIEW(WelcomeView, "Welcome");
    }
}

DesignerViewItf* DesignerViewItf::createView
        (QString viewName, DesignerMainWnd* mainWnd)
{
    initializeIfNotYet();
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
