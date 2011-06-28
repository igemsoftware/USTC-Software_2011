#include "AssemblyItemBrick.h"

const char * AssemblyItemBrick::MimeFormat = "lachesis/AssemblyItemBrick";

AssemblyItemBrick::AssemblyItemBrick( QString & setName , QGraphicsItem *parent ) :
    QGraphicsPixmapItem(parent)
{
    name = setName;
}
