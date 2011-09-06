#ifndef NETWORKVIEWGRAPHICSSCENENODESUBSTANCE_H
#define NETWORKVIEWGRAPHICSSCENENODESUBSTANCE_H
#include "NetworkViewGraphicsSceneNode.h"

class NetworkViewGraphicsSceneNodeSubstance : public NetworkViewGraphicsSceneNode
{
public:
    NetworkViewGraphicsSceneNodeSubstance(QScriptValue value,QGraphicsItem *parent=0,bool isParentContainer = false);
};

#endif // NETWORKVIEWGRAPHICSSCENENODESUBSTANCE_H
