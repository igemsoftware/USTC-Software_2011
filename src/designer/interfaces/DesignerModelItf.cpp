#include <QtDebug>
#include <QScriptValueIterator>

#include "DesignerModelItf.h"

#include "models/reactionnetworkmodel/ReactionNetwork.h"
#include "models/syntheticbiologicalpartmodel/SyntheticBiologicalPart.h"


#define LACHESIS_DECLARE_MODEL(className) \
    DesignerModelItf::ModelItfRegistry::ItemRegistryInlineAdd modelreg_##className (QString( #className ), \
    DesignerModelItf::ModelItfRegistryItem(& className ::staticMetaObject))


void DesignerModelItf::initializeIfNotYet()
{
    static bool initialized = false;
    if(!initialized)
    {
        initialized = true;
        LACHESIS_DECLARE_MODEL(ReactionNetworkModel);
        LACHESIS_DECLARE_MODEL(SyntheticBiologicalPartModel);
    }
}

DesignerModelItf::DesignerModelItf(DesignerDocItf *newDoc) :
    currentDoc(newDoc)
{
}

DesignerModelItf* DesignerModelItf::createModel
        (QString modelName, DesignerDocItf *newDoc)
{
    initializeIfNotYet();

    ModelItfRegistryItem metaObj = ModelItfRegistry::find(modelName);
    if(metaObj.metaObject)
        return dynamic_cast<DesignerModelItf*>
                (metaObj.metaObject->newInstance(Q_ARG(DesignerDocItf*, newDoc)));

    return NULL;
}

DesignerModelItf::modelObjectIndex
DesignerModelItf::createModelObject(modelObjectIndex parent, void* data)
{
    return 1;
}

void DesignerModelItf::removeModelObject(modelObjectIndex index)
{

}

void DesignerModelItf::setModelObjectProperty(modelObjectIndex index, QString propertyName, QString value)
{
}

QString DesignerModelItf::getModelObjectProperty(modelObjectIndex index, QString propertyName)
{
    return "";
}


