#ifndef NETWORKVIEWGRAPHICSSCENENODE_H
#define NETWORKVIEWGRAPHICSSCENENODE_H

#include "NetworkViewGraphicsScene.h"
#include "NetworkViewGraphicsItem.h"

class NetworkViewGraphicsSceneEdge;

class NetworkViewGraphicsSceneNode : public NetworkViewGraphicsItem
{
public:

    enum
    {
        radius = 24
    };

    QList<NetworkViewGraphicsSceneEdge*> edgeList;    
    NetworkViewGraphicsSceneNode(QGraphicsItem *parent , QScriptValue value , QString normalImagePath , QString selectedImagePath , bool isParentContainer = false);
    virtual ~NetworkViewGraphicsSceneNode();
    void registerEdge(NetworkViewGraphicsSceneEdge* edge);
    void updatePos();
    void deleteEdges();
    void deleteEdge(NetworkViewGraphicsSceneEdge * edge);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);

};

#endif // NETWORKVIEWGRAPHICSSCENENODE_H
