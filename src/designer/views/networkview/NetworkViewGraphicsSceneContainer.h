#ifndef NETWORKVIEWGRAPHICSSCENECONTAINER_H
#define NETWORKVIEWGRAPHICSSCENECONTAINER_H

#include "NetworkViewGraphicsItem.h"
#include "NetworkViewGraphicsSceneNode.h"

class NetworkViewGraphicsSceneLabel;

class NetworkViewGraphicsSceneContainer : public NetworkViewGraphicsItem//,public QGraphicsEllipseItem
{
public:
    enum
    {
        radius = 150
    };

    QList<NetworkViewGraphicsSceneNode*> nodeList;

    explicit NetworkViewGraphicsSceneContainer(QGraphicsItem *parent, QScriptValue value);
    int getRadius() {return radius;}
    void registerNode(NetworkViewGraphicsSceneNode* node);
    void setLabel(QString label);
    void updatePos();

private:
    NetworkViewGraphicsSceneLabel* labelObject;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);

};

#endif // NETWORKVIEWGRAPHICSSCENECONTAINER_H
