#include "NetworkViewGraphicsSceneNodeReaction.h"

NetworkViewGraphicsSceneNodeReaction::NetworkViewGraphicsSceneNodeReaction(QGraphicsItem *parent, QScriptValue value, bool isParentContainer)
    :NetworkViewGraphicsSceneNode( parent,value, QObject::tr(":/designer/assemblyview/icon_mol.png") , QObject::tr(":/designer/assemblyview/icon_mol.png") ,isParentContainer )
{
    Type="reaction";
}
