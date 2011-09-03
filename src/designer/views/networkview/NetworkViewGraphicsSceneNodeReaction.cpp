#include "NetworkViewGraphicsSceneNodeReaction.h"

NetworkViewGraphicsSceneNodeReaction::NetworkViewGraphicsSceneNodeReaction(QScriptValue value, QGraphicsItem *parent, bool isParentContainer)
    :NetworkViewGraphicsSceneNode( parent,value, QObject::tr(":/designer/assemblyview/icon_mol.png") , QObject::tr(":/designer/assemblyview/icon_mol.png") ,isParentContainer )
{
    Type="reaction";
}
