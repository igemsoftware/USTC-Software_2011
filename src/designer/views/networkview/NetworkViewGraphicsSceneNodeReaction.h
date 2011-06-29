#ifndef NETWORKVIEWGRAPHICSSCENENODEREACTION_H
#define NETWORKVIEWGRAPHICSSCENENODEREACTION_H

#include "NetworkViewGraphicsSceneNode.h"

class NetworkViewGraphicsSceneNodeReaction : public NetworkViewGraphicsSceneNode
{
public:
    NetworkViewGraphicsSceneNodeReaction(QGraphicsItem *parent);

    virtual int type() { return NetworkViewGraphicsScene::NetworkViewGraphicsItemStartIndex + NodeReaction;}
};

#endif // NETWORKVIEWGRAPHICSSCENENODEREACTION_H
