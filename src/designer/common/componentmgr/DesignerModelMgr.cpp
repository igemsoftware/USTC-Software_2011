#include "DesignerModelMgr.h"
#include "interfaces/DesignerModelItf.h"

#include "models/reactionnetworkmodel/ReactionNetwork.h"
#include "models/syntheticbiologicalpartmodel/SyntheticBiologicalPart.h"
#include "models/igamemodel/IGame.h"


#define LACHESIS_DECLARE_MODEL(className) \
    DesignerModelMgr::ModelItfRegistry::ItemRegistryInlineAdd modelreg_##className (QString( #className ), \
    DesignerModelMgr::ModelItfRegistryItem(& className ::staticMetaObject))


void DesignerModelMgr::initializeIfNotYet()
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

DesignerModelComponent* DesignerModelMgr::createModel
        (QString modelName, DesignerDocComponent *newDoc)
{
    initializeIfNotYet();

    ModelItfRegistryItem metaObj = ModelItfRegistry::find(modelName);
    if(metaObj.metaObject)
        return dynamic_cast<DesignerModelComponent*>
                (metaObj.metaObject->newInstance(Q_ARG(DesignerDocComponent*, newDoc)));

    return NULL;
}
