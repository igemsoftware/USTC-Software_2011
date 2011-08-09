#include "AssemblyItemPart.h"
#include "AssemblyItemPlasmid.h"

const char * AssemblyItemPart::MimeFormat = "lachesis/AssemblyItemPart";

AssemblyItemPart::AssemblyItemPart( QScriptValue & newScriptValue , QGraphicsItem *parent ) :
    AssemblyItemBase( newScriptValue , QObject::tr(":/designer/oops.png") , QObject::tr(":/designer/oops.png") , parent )
{
    type = "part";

    setScriptValue(newScriptValue);
}

AssemblyItemPart::~AssemblyItemPart()
{
}

bool AssemblyItemPart::addChild(QPointF scenePos, AssemblyItemBase *child)
{
    return false;
}

void AssemblyItemPart::setScriptValue(QScriptValue &newScriptValue)
{
    displayName->setPlainText( scriptValue.property("agent").toString() );
    displayName->setTextWidth( pixmap().rect().width() );
    displayName->setPos( ( pixmap().width() - displayName->textWidth() )/2 , pixmap().height() );
}
