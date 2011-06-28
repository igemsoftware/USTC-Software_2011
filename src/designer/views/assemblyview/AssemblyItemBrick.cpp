#include "AssemblyItemBrick.h"

AssemblyItemBrick::AssemblyItemBrick( QString & setName , QGraphicsItem *parent ) :
    QGraphicsPixmapItem(parent)
{
    name = setName;
}
