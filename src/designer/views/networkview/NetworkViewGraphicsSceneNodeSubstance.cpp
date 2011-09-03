#include "NetworkViewGraphicsSceneNodeSubstance.h"

NetworkViewGraphicsSceneNodeSubstance::NetworkViewGraphicsSceneNodeSubstance(QScriptValue value, QGraphicsItem *parent, bool isParentContainer)
    :NetworkViewGraphicsSceneNode( parent,value, QObject::tr(":/designer/assemblyview/icon_protein.png") , QObject::tr(":/designer/assemblyview/icon_protein.png") ,isParentContainer )
{
    Type="substance";
}
