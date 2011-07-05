#include "AssemblyItemPart.h"
#include "AssemblyItemPlasmid.h"

const char * AssemblyItemPart::MimeFormat = "lachesis/AssemblyItemPart";

AssemblyItemPart::AssemblyItemPart( QScriptValue & newScriptValue , QGraphicsItem *parent ) :
    AssemblyItemBase( newScriptValue , QObject::tr(":/designer/oops.png") , QObject::tr(":/designer/oops.png") , parent )
{
    displayName->setTextWidth( pixmap().rect().width() );
    displayName->setPos( ( pixmap().width() - displayName->textWidth() )/2 , pixmap().height() );
}

AssemblyItemPart::~AssemblyItemPart()
{
}

bool AssemblyItemPart::addChild(QPointF scenePos, AssemblyItemBase *child)
{
    return false;
}
