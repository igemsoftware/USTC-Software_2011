#include "NetworkViewGraphicsSceneNodeSubstance.h"

NetworkViewGraphicsSceneNodeSubstance::NetworkViewGraphicsSceneNodeSubstance(QGraphicsItem *parent, QScriptValue value, bool isParentContainer)
    :NetworkViewGraphicsSceneNode( parent,value, QObject::tr(":/designer/assemblyview/icon_protein.png") , QObject::tr(":/designer/assemblyview/icon_protein.png") ,isParentContainer )
{    
}
