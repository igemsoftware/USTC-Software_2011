#ifndef NETWORKVIEWGRAPHICSSCENECONTAINER_H
#define NETWORKVIEWGRAPHICSSCENECONTAINER_H

#include "NetworkViewGraphicsItem.h"
#include "NetworkViewGraphicsSceneNode.h"

class NetworkViewGraphicsSceneLabel;

class NetworkViewGraphicsSceneContainer : public NetworkViewGraphicsItem
{
public:
    enum
    {
        radius = 150
    };    

    explicit NetworkViewGraphicsSceneContainer(QScriptValue value,QGraphicsItem *parent=0);
    int getRadius() {return radius;}
    void setLabel(QString label);
    void updatePos();

private:
    NetworkViewGraphicsSceneLabel* labelObject;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);

};

#endif // NETWORKVIEWGRAPHICSSCENECONTAINER_H
