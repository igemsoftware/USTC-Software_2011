#include "AssemblyItemBrick.h"
#include "AssemblyItemPlasmid.h"

const char * AssemblyItemBrick::MimeFormat = "lachesis/AssemblyItemBrick";

AssemblyItemBrick::AssemblyItemBrick( QString & setName , QGraphicsItem *parent ) :
    QGraphicsPixmapItem(parent)
{
    name = setName;
    QPixmap icon( QObject::tr("://designer//assemblyview//temp.png") );
    icon = icon.scaled( ASSEMBLY_ITEM_BRICK_WIDTH , ASSEMBLY_ITEM_BRICK_HEIGHT );
    setPixmap(icon);

    setFlag( QGraphicsItem::ItemIsSelectable );
    setFlag( QGraphicsItem::ItemIsFocusable );

    displayName = new QGraphicsTextItem( name , this , scene() );
    displayName->setTextWidth( ((qreal)ASSEMBLY_ITEM_BRICK_WIDTH) );
    displayName->setPos( 0 , ASSEMBLY_ITEM_BRICK_HEIGHT );
}

AssemblyItemBrick::~AssemblyItemBrick()
{
    try
    {
        dynamic_cast<AssemblyItemPlasmid*>( parentItem() )->removeBrick(this);
        delete displayName;
    }catch(...)
    {
    }
}
