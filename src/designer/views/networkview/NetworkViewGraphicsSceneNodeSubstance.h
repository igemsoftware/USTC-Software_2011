#ifndef NETWORKVIEWGRAPHICSSCENENODESUBSTANCE_H
#define NETWORKVIEWGRAPHICSSCENENODESUBSTANCE_H

#include "NetworkViewGraphicsSceneNode.h"

class NetworkViewGraphicsSceneNodeSubstance : public NetworkViewGraphicsSceneNode
{
private:
    QBrush privateBrush;
public:
    NetworkViewGraphicsSceneNodeSubstance(QScriptValue value,QGraphicsItem *parent=0,bool isParentContainer = false);

    virtual int type() { return NetworkViewGraphicsScene::NetworkViewGraphicsItemStartIndex + NodeSubstance;}
};

#endif // NETWORKVIEWGRAPHICSSCENENODESUBSTANCE_H
