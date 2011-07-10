#include "NetworkViewGraphicsSceneNodeReaction.h"

NetworkViewGraphicsSceneNodeReaction::NetworkViewGraphicsSceneNodeReaction(QGraphicsItem *parent, bool isParentContainer)
    : NetworkViewGraphicsSceneNode(parent, isParentContainer)
    , privateBrush(Qt::yellow)
{
    setBrush(privateBrush);
}
