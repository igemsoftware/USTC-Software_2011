#include <cmath>
#include "NetworkViewGraphicsSceneModification.h"

const qreal NetworkViewGraphicsSceneModification::radius=2.5;

NetworkViewGraphicsSceneModification::NetworkViewGraphicsSceneModification(QGraphicsItem *parent,
                                                           NetworkViewGraphicsSceneNode* node1,
                                                           NetworkViewGraphicsSceneNode* node2)
    : QGraphicsLineItem(parent),
      edgeNode1 (node1), edgeNode2 (node2)
{
    setFlags( QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsSelectable);
    QPen pen;
    pen.setWidth(1);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    head.setBrush(brush);
    setPen(pen);
    if(edgeNode1)
    {
        edgeNode1->registerMod(this);
    }
    if(edgeNode2)
    {
        edgeNode2->registerMod(this);
    }

    arrowLines.setParentItem(this);
    head.setParentItem(this);
    updatePos();
    setZValue(2);
}

void NetworkViewGraphicsSceneModification::updatePos()
{
    if(edgeNode1&&edgeNode2)
    {
        qreal r  = NetworkViewGraphicsSceneNode::radius;

        qreal x1 = edgeNode1->scenePos().x(), x2 = edgeNode2->scenePos().x();
        qreal y1 = edgeNode1->scenePos().y(), y2 = edgeNode2->scenePos().y();
        qreal a = atan2( y2-y1, x2-x1 );
        qreal sv  = sin(a), cv = cos(a);

        head.setRect( x2 - cv*r+r-radius,y2 - sv*r+r-radius,2*radius,2*radius);
        setLine(x1 + cv*r+r, y1 + sv*r+r, x2 - cv*r+r, y2 - sv*r+r);
    }
}

NetworkViewGraphicsSceneModification::~NetworkViewGraphicsSceneModification()
{
    if(edgeNode2)edgeNode2->deleteMod(this);
    if(edgeNode1)edgeNode1->deleteMod(this);
    dynamic_cast<NetworkViewGraphicsScene *>(this->scene())->removeLine(this);
}
