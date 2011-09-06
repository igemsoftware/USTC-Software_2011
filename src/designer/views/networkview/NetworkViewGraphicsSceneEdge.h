#ifndef NETWORKVIEWGRAPHICSSCENEEDGE_H
#define NETWORKVIEWGRAPHICSSCENEEDGE_H
#include "NetworkViewGraphicsSceneNode.h"
#include <QGraphicsLineItem>

class NetworkViewGraphicsSceneNode;

class NetworkViewGraphicsSceneEdge : public QGraphicsLineItem
{
public:
    enum EdgeType
    {
        UndirectedEdge,
        DirectedEdge,
        BidirectedEdge
    };
    NetworkViewGraphicsSceneNode* edgeNode1;
    NetworkViewGraphicsSceneNode* edgeNode2;
    EdgeType                      edgeType;

    QGraphicsLineItem             arrowLines[4];


    static const qreal arrowLength;
    static const qreal arrowAngle;

    void updatePos(void);
    NetworkViewGraphicsSceneEdge(QGraphicsItem *parent,
                                 NetworkViewGraphicsSceneNode* node1,
                                 NetworkViewGraphicsSceneNode* node2,
                                  EdgeType type);
//    virtual int type() { return NetworkViewGraphicsScene::NetworkViewGraphicsItemStartIndex + 16;}
    virtual ~NetworkViewGraphicsSceneEdge();
};

#endif // NETWORKVIEWGRAPHICSSCENEEDGE_H
