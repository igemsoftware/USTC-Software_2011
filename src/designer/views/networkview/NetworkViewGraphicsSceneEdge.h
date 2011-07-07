#ifndef NETWORKVIEWGRAPHICSSCENEEDGE_H
#define NETWORKVIEWGRAPHICSSCENEEDGE_H

#include <QGraphicsLineItem>
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
private:
    NetworkViewGraphicsSceneLabel* labelObject;
public:
    void setLabel(QString label);
public:
    NetworkViewGraphicsSceneEdge(QGraphicsItem *parent,
                                 NetworkViewGraphicsSceneNode* node1,
                                 NetworkViewGraphicsSceneNode* node2,
                                  EdgeType type);

public:
    void updatePos(void);


    NetworkViewGraphicsSceneNode* edgeNode1;
    NetworkViewGraphicsSceneNode* edgeNode2;
    EdgeType                      edgeType;

    QGraphicsLineItem             arrowLines[4];


    static const qreal arrowLength;
    static const qreal arrowAngle;

    virtual int type() { return NetworkViewGraphicsScene::NetworkViewGraphicsItemStartIndex + 16;}

};

#endif // NETWORKVIEWGRAPHICSSCENEEDGE_H
