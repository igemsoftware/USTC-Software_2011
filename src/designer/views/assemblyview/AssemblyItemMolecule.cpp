#include "AssemblyItemMolecule.h"

const char * AssemblyItemMolecule::MimeFormat = "lachesis/AssemblyItemMolecule";

AssemblyItemMolecule::AssemblyItemMolecule( QScriptValue & newScriptValue , QGraphicsItem *parent ) :
    AssemblyItemBase( newScriptValue , newScriptValue.property("type").toString() == "molecule"?QObject::tr(":/designer/assemblyview/icon_mol.png"):QObject::tr(":/designer/assemblyview/icon_protein.png") , newScriptValue.property("type").toString() == "molecule"?QObject::tr(":/designer/assemblyview/icon_mol.png"):QObject::tr(":/designer/assemblyview/icon_protein.png") , parent )
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
