#include "AssemblyItemCompartment.h"

AssemblyItemCompartment::AssemblyItemCompartment( QString  setName , QGraphicsItem *parent ) :
    QGraphicsEllipseItem(parent)
{
    name = setName;
    setFlag( QGraphicsItem::ItemIsMovable );
    setFlag( QGraphicsItem::ItemIsFocusable );
    setFlag( QGraphicsItem::ItemIsSelectable );
    //pressed = false;
}

/*
void AssemblyItemCompartment::mousePressEvent( QGraphicsSceneMouseEvent * event )
{
    event->accept();
    QGraphicsEllipseItem::mousePressEvent(event);
    pressed = true;
    //hotPoint = event->pos() - this->pos();
}

void AssemblyItemCompartment::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsEllipseItem::mouseReleaseEvent(event);
    //pressed = false;
}

void AssemblyItemCompartment::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    QGraphicsEllipseItem::mouseMoveEvent(event);
    //if( !pressed)
    //setPos( event->pos() - hotPoint );
}
*/
