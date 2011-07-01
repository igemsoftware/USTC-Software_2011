#include "AssemblyItemPlasmid.h"
#include "AssemblyItemCompartment.h"
#include "AssemblyScene.h"

const char * AssemblyItemPlasmid::MimeFormat = "lachesis/AssemblyItemPlasmid";

AssemblyItemPlasmid::AssemblyItemPlasmid( QString newName , QGraphicsItem *parent ) :
    AssemblyItemBase( newName , QObject::tr(":/designer/assemblyview/plasmid_normal.png") , QObject::tr(":/designer/assemblyview/plasmid_selected.png") , parent )
{
}

AssemblyItemPlasmid::~AssemblyItemPlasmid()
{
    foreach( AssemblyItemBase * item , getChildren() )
        delete item;
}

QList<AssemblyItemBase*> AssemblyItemPlasmid::getChildren()
{
    return childrenList;
}


bool AssemblyItemPlasmid::addChild( QPointF scenePos , AssemblyItemBase * child )
{
    if( ! dynamic_cast<AssemblyItemPart*>(child) ) return false;

    scenePos = mapFromScene(scenePos);
    qreal len = scenePos.x() + ASSEMBLY_ITEM_BRICK_WIDTH/2;
    int index = len/ASSEMBLY_ITEM_BRICK_WIDTH;
    if( index < 0 ) len = 0;
    if( index > childrenList.count() ) len = childrenList.count();
    childrenList.insert( index , child );
    AssemblyItemBase::addChild( scenePos , child );

    arrangeChild();
    return true;
}

void AssemblyItemPlasmid::removeChild( AssemblyItemBase * child )
{
    childrenList.removeAll(child);
    AssemblyItemBase::removeChild(child);
    arrangeChild();
}

void AssemblyItemPlasmid::arrangeChild()
{
    resize( (childrenList.count()+1)*ASSEMBLY_ITEM_BRICK_WIDTH , pixmap().height() );
    qreal newx = ASSEMBLY_ITEM_BRICK_WIDTH;
    qreal deltax = newx;
    newx /= 2;
    qreal newy = ( pixmap().height() - ASSEMBLY_ITEM_BRICK_HEIGHT );
    newy /=2 ;
    for( int i = 0 ; i < childrenList.count() ; i++ )
    {
        childrenList[i]->setPos( newx , newy );
        newx += deltax;
    }
}


