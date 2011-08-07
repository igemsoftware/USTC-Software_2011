#include "AssemblyItemCompartment.h"
#include "AssemblyScene.h"

#include <QScriptValueIterator>

const char * AssemblyItemCompartment::MimeFormat = "lachesis/AssemblyItemCompartment";


AssemblyItemCompartment::AssemblyItemCompartment( QScriptValue & newScriptValue , QGraphicsItem *parent ) :
    AssemblyItemBase( newScriptValue , QObject::tr(":/designer/assemblyview/compartment_normal.png") , QObject::tr(":/designer/assemblyview/compartment_selected.png") , parent )
{
    setResizable(true);
}

AssemblyItemCompartment::~AssemblyItemCompartment()
{
    foreach( AssemblyItemBase * item , getChildren() )
        delete item;
}


bool AssemblyItemCompartment::addChild( QPointF scenePos , AssemblyItemBase * child )
{
    if( ( dynamic_cast<AssemblyItemPlasmid*>(child) || ( dynamic_cast<AssemblyItemCompartment*>(child) && parentItem() == 0 && child->boundingRect().width()*child->boundingRect().height() < 0.5*boundingRect().width()*boundingRect().height()  ) ) && !childrenMap.contains( child->getId() ) )
    {
        if( AssemblyItemBase::addChild( scenePos , child ) )
        {
            childrenMap.insert( child->getId() , child );
            refreshScriptValue();
            return true;
        }
    }
    return false;
}



void AssemblyItemCompartment::removeChild( AssemblyItemBase * child )
{
    foreach( QString key , childrenMap.keys() )
    {
        if( childrenMap[key] == child )
        {
            childrenMap.remove(key);
            break;
        }
    }
    AssemblyItemBase::removeChild( child );
    refreshScriptValue();
}

void AssemblyItemCompartment::refreshScriptValue()
{
    QScriptValueList list;
    foreach( AssemblyItemBase * item , getChildren() )
    {
        list.push_back(item->getScriptValue());
    }
    //to be fixed
    scriptValue.setProperty( "contains" , convertModelTypeToScriptValue( scriptValue.engine() , list ) );
}

QList<AssemblyItemBase*> AssemblyItemCompartment::getChildren()
{
    return childrenMap.values();
}






