#include "NetworkViewGraphicsSceneNodeSubstance.h"

NetworkViewGraphicsSceneNodeSubstance::NetworkViewGraphicsSceneNodeSubstance(QGraphicsItem *parent, bool isParentContainer)
    : NetworkViewGraphicsSceneNode(parent, isParentContainer)
    , privateBrush(Qt::red)
{
    setBrush(privateBrush);
}
