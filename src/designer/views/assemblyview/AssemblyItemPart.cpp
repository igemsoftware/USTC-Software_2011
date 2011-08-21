#include "AssemblyItemPart.h"
#include "AssemblyItemPlasmid.h"

const char * AssemblyItemPart::MimeFormat = "lachesis/AssemblyItemPart";

AssemblyItemPart::AssemblyItemPart( QScriptValue & newScriptValue , QGraphicsItem *parent ) :
    AssemblyItemBase( newScriptValue , QObject::tr(":/designer/assemblyview/icon_%1.png").arg(newScriptValue.property("category").toString()) , QObject::tr(":/designer/assemblyview/icon_%1.png").arg(newScriptValue.property("category").toString()) , parent )
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
    scriptValue = newScriptValue;
    displayName->setPlainText( scriptValue.property("agent").toString() );
    displayName->setTextWidth( pixmap().rect().width() );
    displayName->setPos( ( pixmap().width() - displayName->textWidth() )/2 , pixmap().height() );
}


void AssemblyItemPart::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QScriptValueList tmp;
    tmp.push_back( copyFromScriptValue( getScriptValue().engine() , getScriptValue() ) );
    AssemblyPropertyEditor dialog(type,tmp,scriptValue.engine());
    if( dialog.exec() == QDialog::Accepted )
    {
        setScriptValue( tmp[0] );
    }
}
