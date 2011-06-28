#include "AssemblyItemPlasmid.h"

AssemblyItemPlasmid::AssemblyItemPlasmid( QString & setName , QGraphicsItem *parent ) :
    QGraphicsLineItem(parent)
{
    name = setName;
}
