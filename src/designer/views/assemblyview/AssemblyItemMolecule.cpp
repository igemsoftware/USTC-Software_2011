#include "AssemblyItemMolecule.h"

const char * AssemblyItemMolecule::MimeFormat = "lachesis/AssemblyItemMolecule";

AssemblyItemMolecule::AssemblyItemMolecule( QScriptValue & newScriptValue , QGraphicsItem *parent ) :
    AssemblyItemBase( newScriptValue , QObject::tr(":/designer/oops.png") , QObject::tr(":/designer/oops.png") , parent )
{
    type = "molecule";
    displayName->setTextWidth( pixmap().rect().width() );
    displayName->setPos( ( pixmap().width() - displayName->textWidth() )/2 , pixmap().height() );
}

AssemblyItemMolecule::~AssemblyItemMolecule()
{
}

bool AssemblyItemMolecule::addChild(QPointF scenePos, AssemblyItemBase *child)
{
    return false;
}
