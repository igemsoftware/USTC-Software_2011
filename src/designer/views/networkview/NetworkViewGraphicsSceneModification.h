#ifndef NETWORKVIEWGRAPHICSSCENEMODIFICATION_H
#define NETWORKVIEWGRAPHICSSCENEMODIFICATION_H
#include "NetworkViewGraphicsSceneNode.h"
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>

class NetworkViewGraphicsSceneNode;

class NetworkViewGraphicsSceneModification : public QGraphicsLineItem
{
public:    
    QGraphicsLineItem  arrowLines;
    QGraphicsEllipseItem head;
    static const qreal radius;

    NetworkViewGraphicsSceneModification(QGraphicsItem *parent,NetworkViewGraphicsSceneNode* node1,NetworkViewGraphicsSceneNode* node2);
    void updatePos(void);
    virtual ~NetworkViewGraphicsSceneModification();
    NetworkViewGraphicsSceneNode* edgeNode1;
    NetworkViewGraphicsSceneNode* edgeNode2;
};

#endif // NETWORKVIEWGRAPHICSSCENEMODIFICATION_H
