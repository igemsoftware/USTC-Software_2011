#include "AssemblyCreateAndDrag.h"
#include "AssemblyLib.h"
#include <QScriptValueIterator>

AssemblyCreateAndDrag::AssemblyCreateAndDrag( QString newType , QScriptValue newScriptValue , QPixmap newIcon , QWidget *parent) :
    QPushButton(parent)
{
    scriptValue = newScriptValue;
    type = newType;
    icon = newIcon;
    setIcon( icon );
    setFlat(true);
    connect( this , SIGNAL(pressed()) , this , SLOT(createAndDrag()) );
}


void AssemblyCreateAndDrag::createAndDrag()
{

    QByteArray itemData(sizeof(QScriptValue*),0);

    QScriptValue * copy = new QScriptValue( scriptValue.engine()->newObject() );

    QScriptValueIterator iter(scriptValue);
    while( iter.hasNext() )
    {
        iter.next();
        copy->setProperty( iter.name() , iter.value() );
    }

    memcpy( itemData.data() , &copy , sizeof(QScriptValue*) );
    QMimeData * mimeData = new QMimeData;
    mimeData->setData( type , itemData );

    this->setDown(false);

    QDrag * drag = new QDrag(this);
    drag->setMimeData( mimeData );
    drag->setPixmap( icon );
    drag->setHotSpot( QPoint( drag->pixmap().width()/2 , drag->pixmap().height()/2 ) );
    drag->exec();
}
