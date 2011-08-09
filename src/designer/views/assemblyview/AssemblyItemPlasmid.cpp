#include "AssemblyItemPlasmid.h"
#include "AssemblyItemCompartment.h"
#include "AssemblyScene.h"

const char * AssemblyItemPlasmid::MimeFormat = "lachesis/AssemblyItemPlasmid";

AssemblyItemPlasmid::AssemblyItemPlasmid( QScriptValue & newScriptValue , QGraphicsItem *parent ) :
    AssemblyItemBase( newScriptValue , QObject::tr(":/designer/assemblyview/plasmid_normal.png") , QObject::tr(":/designer/assemblyview/plasmid_selected.png") , parent )
{
    type = "plasmid";
    if( scriptValue.property("structure").isArray() )
    {
        QScriptValueList children;
        qScriptValueToSequence( scriptValue.property("structure") , children );
        foreach( QScriptValue child , children )
        {
            if( child.property("type").toString() == "dna" )
            {
                AssemblyItemPart * part = new AssemblyItemPart(child);
                addChild( mapToScene(0,1000000000) , part );
            }
        }
    }
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
    if( ! dynamic_cast<AssemblyItemPart*>(child) || ! AssemblyItemBase::addChild( scenePos , child ) ) return false;

    scenePos = mapFromScene(scenePos);
    qreal len = scenePos.x() + ASSEMBLY_ITEM_BRICK_WIDTH/2;
    int index = len/ASSEMBLY_ITEM_BRICK_WIDTH;
    if( index < 0 ) len = 0;
    if( index > childrenList.count() ) len = childrenList.count();
    childrenList.insert( index , child );

    refreshScriptValue();
    arrangeChild();
    return true;
}

void AssemblyItemPlasmid::removeChild( AssemblyItemBase * child )
{
    childrenList.removeAll(child);
    AssemblyItemBase::removeChild(child);
    refreshScriptValue();
    arrangeChild();
}

void AssemblyItemPlasmid::refreshScriptValue()
{
    QScriptValueList list;
    foreach( AssemblyItemBase * item , getChildren() )
    {
        list.push_back(item->getScriptValue());
    }
    //to be fixed
    scriptValue.setProperty( "structure" , qScriptValueFromSequence( scriptValue.engine() , list ) );
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


