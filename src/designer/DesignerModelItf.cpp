#include "DesignerModelItf.h"

#include "models/reactionnetworkmodel/ReactionNetwork.h"

static QMetaObject metaObjectsOfModels[] = {
    ReactionNetworkModel::staticMetaObject,

};

DesignerModelItf::DesignerModelItf(QObject *parent) :
    QObject(parent)
{
}

DesignerModelItf* DesignerModelItf::createModel
        (QString& modelName)
{
    for(size_t i = 0 ; i < (sizeof(metaObjectsOfModels)/sizeof(metaObjectsOfModels[0])); i++ )
    {
        if(modelName==metaObjectsOfModels[i].className())
        {
            return dynamic_cast<DesignerModelItf*>(metaObjectsOfModels[i].newInstance());
        }
    }
    return NULL;
}
