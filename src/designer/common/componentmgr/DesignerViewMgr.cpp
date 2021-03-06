#include "DesignerViewMgr.h"

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
#include "views/webpageview/WebPageView.h"
#include "views/paramfittingview/ParamFittingView.h"


#define LACHESIS_DECLARE_VIEW(className, titleString, modelName) \
    DesignerViewMgr::ViewItfRegistry::ItemRegistryInlineAdd viewreg_##className (QString( #className ), \
    DesignerViewMgr::ViewItfRegistryItem(& className ::staticMetaObject, QObject::tr(titleString), modelName))


void DesignerViewMgr::initializeIfNotYet()
{
    static bool initialized = false;
    if(!initialized)
    {
        initialized = true;
        LACHESIS_DECLARE_VIEW(AboutView, "About", "");
        LACHESIS_DECLARE_VIEW(AssemblyView, "Assembly View", "IGameModel");
        LACHESIS_DECLARE_VIEW(BehaviorView, "Behavior View", "ReactionNetworkModel");
        LACHESIS_DECLARE_VIEW(ClothoDBView, "Clotho Data Source", "");
        LACHESIS_DECLARE_VIEW(FileDescriptionView, "Views", "");
        LACHESIS_DECLARE_VIEW(NetworkView, "Network View", "ReactionNetworkModel");
        LACHESIS_DECLARE_VIEW(ODEView, "ODE View", "");
        LACHESIS_DECLARE_VIEW(PartView, "Part View", "");
        LACHESIS_DECLARE_VIEW(Plot3DView, "Plot3D View", "");
        LACHESIS_DECLARE_VIEW(SBMLEditorView, "SBML Editor View", "ReactionNetworkModel");
        LACHESIS_DECLARE_VIEW(WelcomeView, "Welcome", "");
        LACHESIS_DECLARE_VIEW(WebPageView, "WebPageView", "");
        //LACHESIS_DECLARE_VIEW(ParamFittingView, "Parameter Fitting View", "");
    }
}

DesignerViewComponent* DesignerViewMgr::createView
        (QString viewName, DesignerMainWnd* mainWnd, DesignerModelComponent* model)
{
    initializeIfNotYet();
    ViewItfRegistryItem metaObj = ViewItfRegistry::find(viewName);
    if(metaObj.metaObject)
        return dynamic_cast<DesignerViewComponent*>
                (metaObj.metaObject->newInstance(Q_ARG(DesignerMainWnd*, mainWnd),
                                                Q_ARG(DesignerModelComponent*, model)));

    return NULL;
}

QString DesignerViewMgr::getViewTitleByName(QString viewName)
{

    ViewItfRegistryItem metaObj = ViewItfRegistry::find(viewName);
    if(metaObj.metaObject->className()==viewName)
        return metaObj.viewTitle;

    return viewName;
}

QString DesignerViewMgr::getViewDefaultModelByName(QString viewName)
{
    return ViewItfRegistry::find(viewName).defaultModelName;
}
QMetaObject DesignerViewMgr::getViewMetaObjectByName(QString viewName)
{
    return *ViewItfRegistry::find(viewName).metaObject;
}

