#include "ReactionNetwork.h"
#include "ReactionNetworkDataTypes.h"
#include "ReactionNetworkSBMLImportProxy.h"

static QMetaObject metaObjectsOfImporters[] = {
    ReactionNetworkSBMLImportProxy::staticMetaObject,
};

DesignerModelFormatProxyItf* ReactionNetworkModel::createImportProxy(QString proxyFormat)
{
    for(size_t i = 0 ; i < (sizeof(metaObjectsOfImporters)/sizeof(metaObjectsOfImporters[0])); i++ )
    {
        if(proxyFormat==metaObjectsOfImporters[i].className())
        {
            return dynamic_cast<DesignerModelFormatProxyItf*>
                    (metaObjectsOfImporters[i].newInstance(Q_ARG(ReactionNetworkModel*, this)));
        }
    }

    return NULL;
}

ReactionNetworkModel::ReactionNetworkModel(DesignerDocItf *newDoc) :
    DesignerModelItf(newDoc)
{
}


QStringList ReactionNetworkModel::getSupportedViewList() const
{
    QStringList supportedViewList;
    supportedViewList.append("AssemblyView");
    supportedViewList.append("NetworkView");
    supportedViewList.append("BehaviorView");
    supportedViewList.append("SBMLEditorView");
    //! \bug For debug purpose.
    supportedViewList.append("Plot3DView");
    supportedViewList.append("PartView");
    supportedViewList.append("ODEView");
    supportedViewList.append("ClothoDBView");
    supportedViewList.append("WebPageView");

    return supportedViewList;
}

