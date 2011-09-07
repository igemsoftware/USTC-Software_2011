#ifndef NETWORKVIEWGRAPHICSSCENENODESUBSTANCE_H
#define NETWORKVIEWGRAPHICSSCENENODESUBSTANCE_H
#include "NetworkViewGraphicsSceneNode.h"

class NetworkViewGraphicsSceneNodeSubstance : public NetworkViewGraphicsSceneNode
{
public:
    NetworkViewGraphicsSceneNodeSubstance(QScriptValue value,QGraphicsItem *parent=0,bool isParentContainer = false);
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // NETWORKVIEWGRAPHICSSCENENODESUBSTANCE_H
