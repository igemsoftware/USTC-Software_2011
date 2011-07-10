#include "ReactionNetwork.h"
#include "ReactionNetworkDataTypes.h"
#include "ReactionNetworkSBMLImportProxy.h"
#include "ReactionNetworkMoDeLImportProxy.h"

static QMetaObject metaObjectsOfImporters[] = {
    ReactionNetworkSBMLImportProxy::staticMetaObject,
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

ReactionNetworkModel::ReactionNetworkModel(QObject *parent) :
    DesignerModelItf(parent)
{
}

ReactionNetworkModel::modelObjectIndex
ReactionNetworkModel::createModelObject(modelObjectIndex parent, void* data)
{
    return 1;
}

void ReactionNetworkModel::removeModelObject(modelObjectIndex index)
{

}

#include <stdio.h>
void ReactionNetworkModel::setModelObjectProperty(modelObjectIndex index, QString propertyName, QString value)
{
//    printf(propertyName.toLatin1().data());
//    printf(value.toLatin1().data());
}

QString ReactionNetworkModel::getModelObjectProperty(modelObjectIndex index, QString propertyName)
{
    return "";
}

