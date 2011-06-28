#include "AssemblyItemPlasmid.h"

const char * AssemblyItemPlasmid::MimeFormat = "lachesis/AssemblyItemPlasmid";

AssemblyItemPlasmid::AssemblyItemPlasmid( QString & setName , QGraphicsItem *parent ) :
    QGraphicsLineItem(parent)
{
    name = setName;
}
