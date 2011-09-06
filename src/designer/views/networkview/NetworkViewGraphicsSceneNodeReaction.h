#ifndef NETWORKVIEWGRAPHICSSCENENODEREACTION_H
#define NETWORKVIEWGRAPHICSSCENENODEREACTION_H
#include "NetworkViewGraphicsSceneNode.h"

class NetworkViewGraphicsSceneNodeReaction : public NetworkViewGraphicsSceneNode
{
public:
    NetworkViewGraphicsSceneNodeReaction(QScriptValue value,QGraphicsItem *parent=0,bool isParentContainer = false);
};

#endif // NETWORKVIEWGRAPHICSSCENENODEREACTION_H
