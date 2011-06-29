#include "AssemblyItemPlasmid.h"
#include "AssemblyItemCompartment.h"
#include "AssemblyScene.h"

const char * AssemblyItemPlasmid::MimeFormat = "lachesis/AssemblyItemPlasmid";

AssemblyItemPlasmid::AssemblyItemPlasmid( QString & setName , QGraphicsItem *parent ) :
    QGraphicsRectItem(parent)
{
    name = setName;
    setFlag( QGraphicsItem::ItemIsMovable );
    setFlag( QGraphicsItem::ItemIsFocusable );
    setFlag( QGraphicsItem::ItemIsSelectable );
    setRect( 0 , 0 , DefaultWidth , DefaultHeight );

    displayName = new QGraphicsTextItem( name , this , scene() );
    displayName->adjustSize();
    qreal rtextwidth = displayName->textWidth();
    displayName->setPos( -rtextwidth , -rect().height() );
}


void AssemblyItemPlasmid::addBrick( QPointF eventPos , AssemblyItemBrick * brick )
{
    eventPos = mapFromScene(eventPos);
    qreal len = eventPos.x();
    int index = len/ASSEMBLY_ITEM_BRICK_WIDTH;
    bricks.insert( index , brick );
    brick->setParentItem(this);

    arrangeBricks();
}

void AssemblyItemPlasmid::removeBrick( AssemblyItemBrick *brick )
{
    try
    {
        bricks.removeAll(brick);
        dynamic_cast<AssemblyScene*>(scene())->removeItem(brick);
        arrangeBricks();
    }catch(...)
    {
    }
}

void AssemblyItemPlasmid::arrangeBricks()
{
    setRect( rect().x() , rect().y() , (bricks.count()+1)*ASSEMBLY_ITEM_BRICK_WIDTH , DefaultHeight );
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

AssemblyItemPlasmid::~AssemblyItemPlasmid()
{
    try
    {
        foreach( AssemblyItemBrick * brick , bricks )
        {
            delete brick;
        }
        dynamic_cast<AssemblyItemCompartment*>( parentItem() )->removePlasmid(this);
        delete displayName;
    }catch(...)
    {
    }
}

void AssemblyItemPlasmid::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsRectItem::mouseReleaseEvent(event);
    if( !collidesWithItem( parentItem() ) )
    {
        AssemblyItemCompartment * newparent = 0;
        QList<QGraphicsItem*> items = collidingItems();
        foreach( QGraphicsItem * item , items )
        {
            if( dynamic_cast<AssemblyItemCompartment*>(item) != 0 )
            {
                if( !newparent ) newparent = dynamic_cast<AssemblyItemCompartment*>(item);
                if( newparent->parentItem() == 0 && dynamic_cast<AssemblyItemCompartment*>(item)->parentItem() != 0 ) newparent = dynamic_cast<AssemblyItemCompartment*>(item);
            }
        }
        QPointF tempPos = scenePos();
        AssemblyItemCompartment * oldparent = dynamic_cast<AssemblyItemCompartment*>(parentItem());
        oldparent->removePlasmid(this);

        if( newparent )
        {
            dynamic_cast<AssemblyItemCompartment*>(newparent)->addPlasmid(tempPos,this);
        }else
        {
            oldparent->scene()->clearSelection();
            oldparent->scene()->clearFocus();
        }
    }
}
