#ifndef NETWORKVIEWGRAPHICSSCENENODE_H
#define NETWORKVIEWGRAPHICSSCENENODE_H

#include <QGraphicsEllipseItem>
#include "NetworkViewGraphicsScene.h"

class NetworkViewGraphicsSceneEdge;
class NetworkViewGraphicsSceneLabel;

class NetworkViewGraphicsSceneNode : public QGraphicsEllipseItem
{
public:
    NetworkViewGraphicsSceneNode(QGraphicsItem *parent);
private:
    NetworkViewGraphicsSceneLabel* labelObject;
public:
    void setLabel(QString label);
public:
    void registerEdge(NetworkViewGraphicsSceneEdge* edge);
    QList<NetworkViewGraphicsSceneEdge*> edgeList;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);

public:
    enum
    {
        NodeAbstract = 0,
        NodeSubstance = 1,
        NodeReaction = 2
    };

    enum
    {
        radius = 12
    };


    virtual int type() { return NetworkViewGraphicsScene::NetworkViewGraphicsItemStartIndex + NodeAbstract;}
};

#endif // NETWORKVIEWGRAPHICSSCENENODE_H
