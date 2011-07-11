#include "NetworkViewGraphicsSceneNodeReaction.h"

NetworkViewGraphicsSceneNodeReaction::NetworkViewGraphicsSceneNodeReaction(QGraphicsItem *parent, QScriptValue value, bool isParentContainer)
    : NetworkViewGraphicsSceneNode(parent, value, isParentContainer)
    , privateBrush(Qt::yellow)
{
    setBrush(privateBrush);
}
