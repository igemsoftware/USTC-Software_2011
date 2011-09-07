#ifndef NETWORKVIEWGRAPHICSSCENECONTAINER_H
#define NETWORKVIEWGRAPHICSSCENECONTAINER_H

#include "NetworkViewGraphicsItem.h"
#include "NetworkViewGraphicsSceneNode.h"

class NetworkViewGraphicsSceneContainer : public NetworkViewGraphicsItem
{
public:
    enum
    {
        radius = 150
    };    

    explicit NetworkViewGraphicsSceneContainer(QScriptValue value,QGraphicsItem *parent=0);
    int getRadius() {return radius;}
    void updatePos();
    virtual bool addChild( QPointF scenePos , NetworkViewGraphicsItem * child );

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // NETWORKVIEWGRAPHICSSCENECONTAINER_H
