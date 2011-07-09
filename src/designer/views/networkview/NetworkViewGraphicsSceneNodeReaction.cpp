#include "NetworkViewGraphicsSceneNodeReaction.h"

NetworkViewGraphicsSceneNodeReaction::NetworkViewGraphicsSceneNodeReaction(QGraphicsItem *parent)
    : NetworkViewGraphicsSceneNode(parent)
    , privateBrush(Qt::yellow)
{
    setBrush(privateBrush);
}
