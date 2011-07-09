#include "NetworkViewGraphicsSceneNodeSubstance.h"

NetworkViewGraphicsSceneNodeSubstance::NetworkViewGraphicsSceneNodeSubstance(QGraphicsItem *parent)
    : NetworkViewGraphicsSceneNode(parent)
    , privateBrush(Qt::red)
{
    setBrush(privateBrush);
}
