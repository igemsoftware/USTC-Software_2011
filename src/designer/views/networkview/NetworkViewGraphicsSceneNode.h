#ifndef NETWORKVIEWGRAPHICSSCENENODE_H
#define NETWORKVIEWGRAPHICSSCENENODE_H

#include <QtScript>
#include <QGraphicsEllipseItem>
#include "NetworkViewGraphicsScene.h"

#include "NetworkViewGraphicsItem.h"

class NetworkViewGraphicsSceneEdge;
class NetworkViewGraphicsSceneLabel;

class NetworkViewGraphicsSceneNode : public QGraphicsEllipseItem,
        public NetworkViewGraphicsItem
{
public:
    NetworkViewGraphicsSceneNode(QGraphicsItem *parent, QScriptValue value, bool isParentContainer = false);
private:
    NetworkViewGraphicsSceneLabel* labelObject;
public:
    void setLabel(QString label);
public:
    void registerEdge(NetworkViewGraphicsSceneEdge* edge);
    QList<NetworkViewGraphicsSceneEdge*> edgeList;

    void updatePos();

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
