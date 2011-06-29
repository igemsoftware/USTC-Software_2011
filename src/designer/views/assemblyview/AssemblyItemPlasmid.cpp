#include "AssemblyItemPlasmid.h"

const char * AssemblyItemPlasmid::MimeFormat = "lachesis/AssemblyItemPlasmid";

AssemblyItemPlasmid::AssemblyItemPlasmid( QString & setName , QGraphicsItem *parent ) :
    QGraphicsRectItem(parent)
{
    name = setName;
    setFlag( QGraphicsItem::ItemIsMovable );
    setFlag( QGraphicsItem::ItemIsFocusable );
    setFlag( QGraphicsItem::ItemIsSelectable );
    setRect( 0 , 0 , DefaultWeight , DefaultHeight );

}


void AssemblyItemPlasmid::addBrick( QPointF eventPos , AssemblyItemBrick * brick )
{
    eventPos = mapFromScene(eventPos);
    qreal len = eventPos.x();
    int index = len/ASSEMBLY_ITEM_BRICK_WIDTH;
    bricks.insert( index , brick );
    brick->setParentItem(this);
    setRect( rect().x() , rect().y() , rect().width()+ASSEMBLY_ITEM_BRICK_WIDTH , DefaultHeight );
    qreal newx = ASSEMBLY_ITEM_BRICK_WIDTH;
    qreal deltax = newx;
    newx /= 2;
    qreal newy = ( DefaultHeight - ASSEMBLY_ITEM_BRICK_HEIGHT );
    newy /=2 ;
    for( int i = 0 ; i < bricks.count() ; i++ )
    {
        bricks[i]->setPos( newx , newy );
        newx += deltax;
    }
}
