#include "ReactionNetwork.h"
#include "ReactionNetworkDataTypes.h"

ReactionNetworkModel::ReactionNetworkModel(DesignerDocComponent *newDoc) :
    DesignerModelComponent(newDoc)
{
}


QStringList ReactionNetworkModel::getSupportedViewList() const
{
    QStringList supportedViewList;    
    supportedViewList.append("NetworkView");
    supportedViewList.append("BehaviorView");
    supportedViewList.append("SBMLEditorView");
    //! \bug For debug purpose.
    supportedViewList.append("Plot3DView");
    supportedViewList.append("ODEView");
    supportedViewList.append("ClothoDBView");
    supportedViewList.append("WebPageView");

    return supportedViewList;
}

QStringList ReactionNetworkModel::getSupportedDocumentList() const
{
    QStringList supportedDocumentList;
    supportedDocumentList.append("USMLDoc");
    supportedDocumentList.append("SBMLDoc");
    supportedDocumentList.append("MoDeL1Doc");
    return supportedDocumentList;
}


