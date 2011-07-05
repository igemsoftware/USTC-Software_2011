#include "AssemblyCreateAndDrag.h"

AssemblyCreateAndDrag::AssemblyCreateAndDrag( QString newType , QScriptValue newScriptValue , QPixmap newIcon , QWidget *parent) :
    QToolButton(parent)
{
    scriptValue = newScriptValue;
    type = newType;
    icon = newIcon;
    setText( scriptValue.property("name").toString() );
    setIcon( icon );
    connect( this , SIGNAL(pressed()) , this , SLOT(createAndDrag()) );
}


void AssemblyCreateAndDrag::createAndDrag()
{

    QByteArray itemData(sizeof(QScriptValue*),0);
    QScriptValue * copy = &scriptValue; //assume we can copy here
    memcpy( itemData.data() , &copy , sizeof(QScriptValue*) );
    QMimeData * mimeData = new QMimeData;
    mimeData->setData( type , itemData );

    QDrag * drag = new QDrag(this);
    drag->setMimeData( mimeData );
    drag->setPixmap( icon );
    drag->setHotSpot( QPoint( drag->pixmap().width()/2 , drag->pixmap().height()/2 ) );
    drag->exec();
}
