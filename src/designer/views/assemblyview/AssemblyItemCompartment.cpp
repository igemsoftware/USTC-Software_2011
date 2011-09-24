#include "AssemblyItemCompartment.h"
#include "AssemblyScene.h"

#include <QScriptValueIterator>

const char * AssemblyItemCompartment::MimeFormat = "lachesis/AssemblyItemCompartment";


AssemblyItemCompartment::AssemblyItemCompartment( QScriptValue & newScriptValue , QGraphicsItem *parent ) :
    AssemblyItemBase( newScriptValue , QObject::tr(":/designer/assemblyview/compartment_normal.png") , QObject::tr(":/designer/assemblyview/compartment_selected.png") , parent )
{
    type = "compartment";
    setResizable(true);

    if( scriptValue.property("contains").isArray() )
    {
        QScriptValueList children;
        qScriptValueToSequence( scriptValue.property("contains") , children );
        int width = boundingRect().width();
        int height = boundingRect().height();
        foreach( QScriptValue child , children )
        {
            if( child.property("type").toString() == "plasmid" )
            {
                AssemblyItemPlasmid * plasmid = new AssemblyItemPlasmid(child);
                int childwidth = plasmid->boundingRect().width()/2;
                int childheight = plasmid->boundingRect().height()/2;
                addChild( QPointF(qrand()%(width-childwidth), qrand()%(height-childheight)) , plasmid );
            }else if( child.property("type").toString() == "protein" || child.property("type").toString() == "molecule" )
            {
                AssemblyItemMolecule * molecule = new AssemblyItemMolecule(child);
                int childwidth = molecule->boundingRect().width()/2;
                int childheight = molecule->boundingRect().height()/2;
                addChild( QPointF(qrand()%(width-childwidth), qrand()%(height-childheight)) , molecule );
            }
        }
    }
}

AssemblyItemCompartment::~AssemblyItemCompartment()
{
    foreach( AssemblyItemBase * item , getChildren() )
        delete item;
}


bool AssemblyItemCompartment::addChild( QPointF pos , AssemblyItemBase * child )
{
    if( ((dynamic_cast<AssemblyItemMolecule*>(child) )||dynamic_cast<AssemblyItemPart*>(child))  ) return false;
    if( ( dynamic_cast<AssemblyItemPlasmid*>(child) || dynamic_cast<AssemblyItemMolecule*>(child) ) && !childrenMap.contains( child->getId() ) )
    {
        if( AssemblyItemBase::addChild( pos , child ) )
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






