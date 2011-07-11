#ifndef NETWORKVIEWGRAPHICSSCENECONTAINER_H
#define NETWORKVIEWGRAPHICSSCENECONTAINER_H

#include <QtScript>
#include <QGraphicsItem>

#include "NetworkViewGraphicsItem.h"
#include "NetworkViewGraphicsSceneNode.h"

class NetworkViewGraphicsSceneLabel;

class NetworkViewGraphicsSceneContainer : public QGraphicsEllipseItem, public NetworkViewGraphicsItem
{
public:
    explicit NetworkViewGraphicsSceneContainer(QGraphicsItem *parent, QScriptValue value);
private:
    NetworkViewGraphicsSceneLabel* labelObject;

public:
    void registerNode(NetworkViewGraphicsSceneNode* node);
    QList<NetworkViewGraphicsSceneNode*> nodeList;

    void updatePos();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);


public:
    enum
    {
        radius = 150
    };

    int getRadius() {return radius;}

};

#endif // NETWORKVIEWGRAPHICSSCENECONTAINER_H
