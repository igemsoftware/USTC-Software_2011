#ifndef NETWORKVIEWGRAPHICSSCENENODE_H
#define NETWORKVIEWGRAPHICSSCENENODE_H

#include "NetworkViewGraphicsScene.h"
#include "NetworkViewGraphicsItem.h"
#include "NetworkViewGraphicsSceneModification.h"

class NetworkViewGraphicsSceneEdge;
class NetworkViewGraphicsSceneModification;

class NetworkViewGraphicsSceneNode : public NetworkViewGraphicsItem
{
public:

    enum
    {
        radius = 24
    };

    QList<NetworkViewGraphicsSceneEdge*> edgeList;
    QList<NetworkViewGraphicsSceneModification*> modList;
    NetworkViewGraphicsSceneNode(QGraphicsItem *parent , QScriptValue value , QString normalImagePath , QString selectedImagePath , bool isParentContainer = false);
    virtual ~NetworkViewGraphicsSceneNode();
    void registerEdge(NetworkViewGraphicsSceneEdge* edge);
    void registerMod(NetworkViewGraphicsSceneModification* mod);
    void updatePos();
    void deleteEdgesAndMods();
    void deleteEdge(NetworkViewGraphicsSceneEdge * edge);
    void deleteMod(NetworkViewGraphicsSceneModification * mod);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);

};

#endif // NETWORKVIEWGRAPHICSSCENENODE_H
