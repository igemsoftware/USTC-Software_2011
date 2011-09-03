#ifndef NETWORKVIEWGRAPHICSSCENENODEREACTION_H
#define NETWORKVIEWGRAPHICSSCENENODEREACTION_H

#include "NetworkViewGraphicsSceneNode.h"

class NetworkViewGraphicsSceneNodeReaction : public NetworkViewGraphicsSceneNode
{
private:
    QBrush privateBrush;
public:
    NetworkViewGraphicsSceneNodeReaction(QScriptValue value,QGraphicsItem *parent=0,bool isParentContainer = false);

    virtual int type() { return NetworkViewGraphicsScene::NetworkViewGraphicsItemStartIndex + NodeReaction;}
};

#endif // NETWORKVIEWGRAPHICSSCENENODEREACTION_H
