#include "AssemblyItemSizer.h"
#include "AssemblyItemCompartment.h"

AssemblyItemSizer::AssemblyItemSizer( qreal px , qreal py , QGraphicsItem *parent) :
    QGraphicsRectItem(parent)
{
    father = dynamic_cast<AssemblyItemCompartment*>(parent);
    setRect( px - 2 , py - 2 , 4 , 4 );
    setFlag( QGraphicsItem::ItemIsSelectable );
    setFlag( QGraphicsItem::ItemIsMovable );
    hide();
}

void AssemblyItemSizer::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsRectItem::mouseMoveEvent(event);
    QPointF point = mapToParent(mapFromScene(event->scenePos()));
    father->resize( point.x()+2 , point.y()+2 );
}
