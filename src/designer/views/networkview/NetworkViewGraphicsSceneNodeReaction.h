#ifndef NETWORKVIEWGRAPHICSSCENENODEREACTION_H
#define NETWORKVIEWGRAPHICSSCENENODEREACTION_H

#include "NetworkViewGraphicsSceneNode.h"

class NetworkViewGraphicsSceneNodeReaction : public NetworkViewGraphicsSceneNode
{
private:
    QBrush privateBrush;
public:
    NetworkViewGraphicsSceneNodeReaction(QGraphicsItem *parent, QScriptValue value, bool isParentContainer = false);

    virtual int type() { return NetworkViewGraphicsScene::NetworkViewGraphicsItemStartIndex + NodeReaction;}
};

#endif // NETWORKVIEWGRAPHICSSCENENODEREACTION_H
