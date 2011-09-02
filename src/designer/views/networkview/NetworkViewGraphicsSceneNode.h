#ifndef NETWORKVIEWGRAPHICSSCENENODE_H
#define NETWORKVIEWGRAPHICSSCENENODE_H

#include "NetworkViewGraphicsScene.h"
#include "NetworkViewGraphicsItem.h"

class NetworkViewGraphicsSceneEdge;
class NetworkViewGraphicsSceneLabel;

class NetworkViewGraphicsSceneNode : public NetworkViewGraphicsItem
{
public:
    enum
    {
        NodeAbstract = 0,
        NodeSubstance = 1,
        NodeReaction = 2
    };

    enum
    {
        radius = 24
    };

    QList<NetworkViewGraphicsSceneEdge*> edgeList;    
    NetworkViewGraphicsSceneNode(QGraphicsItem *parent , QScriptValue value , QString normalImagePath , QString selectedImagePath , bool isParentContainer = false);
    void setLabel(QString label);
    void registerEdge(NetworkViewGraphicsSceneEdge* edge);
    void updatePos();
    void deleteEdges();
    void deleteEdge(NetworkViewGraphicsSceneEdge * edge);
    virtual int type() { return NetworkViewGraphicsScene::NetworkViewGraphicsItemStartIndex + NodeAbstract;}

private:
    NetworkViewGraphicsSceneLabel* labelObject;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);

};

#endif // NETWORKVIEWGRAPHICSSCENENODE_H
