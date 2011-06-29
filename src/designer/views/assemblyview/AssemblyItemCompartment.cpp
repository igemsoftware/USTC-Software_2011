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
    setRect( 0 , 0 , DefaultWidth , DefaultHeight );

    displayName = new QGraphicsTextItem( name , this , scene() );
    displayName->adjustSize();
    qreal rwidth = rect().width();
    qreal rheight = rect().height();
    qreal rtextwidth = displayName->textWidth();
    displayName->setPos( ( rwidth - rtextwidth )/2 , rheight );

}

void AssemblyItemCompartment::addPlasmid( QPointF pos , AssemblyItemPlasmid * plasmid )
{
    plasmid->setParentItem(this);
    plasmid->setPos( mapFromScene(pos) );
    plasmidMap.insert( plasmid->name , plasmid );
}


AssemblyItemCompartment::~AssemblyItemCompartment()
{
    try
    {
        foreach( AssemblyItemPlasmid * plasmid , plasmidMap.values() )
        {
            delete plasmid;
        }
        dynamic_cast<AssemblyScene*>(scene())->removeItem(this);
        delete displayName;
    }catch(...)
    {
    }
}

void AssemblyItemCompartment::removePlasmid( AssemblyItemPlasmid * plasmid )
{
    foreach( QString key , plasmidMap.keys() )
    {
        if( plasmidMap[key] == plasmid )
        {
            plasmidMap.remove(key);
            break;
        }
    }
    dynamic_cast<AssemblyScene*>(scene())->removeItem(plasmid);
}


void AssemblyItemCompartment::resize( bool magnify )
{
    qreal newHeight = rect().height();
    qreal newWidth = rect().width();
    if( magnify )
    {
        newHeight += DefaultHeight/2;
        newWidth  += DefaultWidth/2;
    }else
    {
        newHeight -= DefaultHeight/2;
        newWidth  -= DefaultWidth/2;
    }
    if( newHeight < DefaultHeight/2 )
    {
        return;
    }
    foreach( AssemblyItemPlasmid * plasmid , plasmidMap.values() )
    {
        plasmid->setPos( plasmid->pos().x()*(plasmid->pos().x()>0?newWidth/rect().width():1) , plasmid->pos().y()*(plasmid->pos().y()>0?newHeight/rect().height():1) );
    }
    qreal rwidth = newWidth;
    qreal rheight = newHeight;
    qreal rtextwidth = displayName->textWidth();
    displayName->setPos( ( rwidth - rtextwidth )/2 , rheight );

    setRect( rect().x() , rect().y() , newWidth , newHeight );
}









