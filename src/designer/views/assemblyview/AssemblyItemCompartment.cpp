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

















