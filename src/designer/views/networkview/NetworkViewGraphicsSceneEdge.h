#ifndef NETWORKVIEWGRAPHICSSCENEEDGE_H
#define NETWORKVIEWGRAPHICSSCENEEDGE_H

#include "NetworkViewGraphicsScene.h"
#include "NetworkViewGraphicsSceneNode.h"

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

    void setLabel(QString label);
    void updatePos(void);
    NetworkViewGraphicsSceneEdge(QGraphicsItem *parent,
                                 NetworkViewGraphicsSceneNode* node1,
                                 NetworkViewGraphicsSceneNode* node2,
                                  EdgeType type);
    virtual int type() { return NetworkViewGraphicsScene::NetworkViewGraphicsItemStartIndex + 16;}

private:
    NetworkViewGraphicsSceneLabel* labelObject;

};

#endif // NETWORKVIEWGRAPHICSSCENEEDGE_H
