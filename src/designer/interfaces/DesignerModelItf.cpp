#include <QtDebug>
#include <QScriptValueIterator>

#include "DesignerModelItf.h"

#include "models/reactionnetworkmodel/ReactionNetwork.h"

static QMetaObject metaObjectsOfModels[] = {
    ReactionNetworkModel::staticMetaObject,

};

DesignerModelItf::DesignerModelItf(DesignerDocItf *newDoc) :
    currentDoc(newDoc)
{
}

DesignerModelItf* DesignerModelItf::createModel
        (QString modelName, DesignerDocItf *newDoc)
{
    for(size_t i = 0 ; i < (sizeof(metaObjectsOfModels)/sizeof(metaObjectsOfModels[0])); i++ )
    {
        if(modelName==metaObjectsOfModels[i].className())
        {
            return dynamic_cast<DesignerModelItf*>(metaObjectsOfModels[i].newInstance(
                                                       Q_ARG(DesignerDocItf*, newDoc)));
        }
    }
    return NULL;
}
