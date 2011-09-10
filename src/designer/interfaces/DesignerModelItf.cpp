#include <QtDebug>
#include <QScriptValueIterator>

#include "DesignerModelItf.h"

#include "models/reactionnetworkmodel/ReactionNetwork.h"
#include "models/syntheticbiologicalpartmodel/SyntheticBiologicalPart.h"
#include "models/igamemodel/IGame.h"

#define LACHESIS_DECLARE_MODEL(className) \
    DesignerModelComponent::ModelItfRegistry::ItemRegistryInlineAdd modelreg_##className (QString( #className ), \
    DesignerModelComponent::ModelItfRegistryItem(& className ::staticMetaObject))


void DesignerModelComponent::initializeIfNotYet()
{
    static bool initialized = false;
    if(!initialized)
    {
        initialized = true;
        LACHESIS_DECLARE_MODEL(ReactionNetworkModel);
        LACHESIS_DECLARE_MODEL(SyntheticBiologicalPartModel);
        LACHESIS_DECLARE_MODEL(IGameModel);
    }
}

DesignerModelComponent::DesignerModelComponent(DesignerDocComponent *newDoc) :
    currentDoc(newDoc),
    modified(false)
{
}

DesignerModelComponent* DesignerModelComponent::createModel
        (QString modelName, DesignerDocComponent *newDoc)
{
    initializeIfNotYet();

    ModelItfRegistryItem metaObj = ModelItfRegistry::find(modelName);
    if(metaObj.metaObject)
        return dynamic_cast<DesignerModelComponent*>
                (metaObj.metaObject->newInstance(Q_ARG(DesignerDocComponent*, newDoc)));

    return NULL;
}

DesignerModelComponent::modelObjectIndex
DesignerModelComponent::createModelObject(modelObjectIndex parent, void* data)
{
    return 1;
}

void DesignerModelComponent::removeModelObject(modelObjectIndex index)
{

}

void DesignerModelComponent::setModelObjectProperty(modelObjectIndex index, QString propertyName, QString value)
{
}

QString DesignerModelComponent::getModelObjectProperty(modelObjectIndex index, QString propertyName)
{
    return "";
}


