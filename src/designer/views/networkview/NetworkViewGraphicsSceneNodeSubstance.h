#ifndef NETWORKVIEWGRAPHICSSCENENODESUBSTANCE_H
#define NETWORKVIEWGRAPHICSSCENENODESUBSTANCE_H

#include "NetworkViewGraphicsSceneNode.h"

class NetworkViewGraphicsSceneNodeSubstance : public NetworkViewGraphicsSceneNode
{
public:
    NetworkViewGraphicsSceneNodeSubstance(QGraphicsItem *parent);

    virtual int type() { return NetworkViewGraphicsScene::NetworkViewGraphicsItemStartIndex + NodeSubstance;}
};

#endif // NETWORKVIEWGRAPHICSSCENENODESUBSTANCE_H
