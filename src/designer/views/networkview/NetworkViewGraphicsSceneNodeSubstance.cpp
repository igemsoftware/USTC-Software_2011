#include "NetworkViewGraphicsSceneNodeSubstance.h"

NetworkViewGraphicsSceneNodeSubstance::NetworkViewGraphicsSceneNodeSubstance(QGraphicsItem *parent, QScriptValue value, bool isParentContainer)
    : NetworkViewGraphicsSceneNode(parent, value, isParentContainer)
    , privateBrush(Qt::red)
{
    setBrush(privateBrush);
}
