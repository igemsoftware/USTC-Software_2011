#include "AssemblyItemCompartment.h"
#include "AssemblyScene.h"

const char * AssemblyItemCompartment::MimeFormat = "lachesis/AssemblyItemCompartment";


AssemblyItemCompartment::AssemblyItemCompartment( QString  setName , QGraphicsItem *parent ) :
    QGraphicsEllipseItem(parent)
{
    name = setName;
    setFlag( QGraphicsItem::ItemIsMovable );
    setFlag( QGraphicsItem::ItemIsFocusable );
    setFlag( QGraphicsItem::ItemIsSelectable );
    setRect( 0 , 0 , DefaultWeight , DefaultHeight );

    QGraphicsTextItem * tempText = new QGraphicsTextItem( name , this , scene() );
    tempText->adjustSize();
    qreal rwidth = rect().width();
    qreal rheight = rect().height();
    qreal rtextwidth = tempText->textWidth();
    tempText->setPos( ( rwidth - rtextwidth )/2 , rheight );
}

void AssemblyItemCompartment::addPlasmid( QPointF pos , AssemblyItemPlasmid * plasmid )
{
    plasmid->setParentItem(this);
    plasmid->setPos( mapFromScene(pos) );
    plasmidMap.insert( plasmid->name , plasmid );
}




















