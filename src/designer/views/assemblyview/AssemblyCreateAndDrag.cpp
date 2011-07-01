#include "AssemblyCreateAndDrag.h"

AssemblyCreateAndDrag::AssemblyCreateAndDrag( QString setType , QString setName , QWidget *parent) :
    QToolButton(parent)
{
    name = setName;
    type = setType;
    setText( name );
    connect( this , SIGNAL(pressed()) , this , SLOT(createAndDrag()) );
}


void AssemblyCreateAndDrag::createAndDrag()
{
    QByteArray itemData = name.toUtf8();
    QMimeData * mimeData = new QMimeData;
    mimeData->setData( type , itemData );

    QDrag * drag = new QDrag(this);
    drag->setMimeData( mimeData );
    drag->setPixmap( QPixmap( tr(":/designer/oops.png") ) );
    drag->setHotSpot( QPoint( drag->pixmap().width()/2 , drag->pixmap().height()/2 ) );
    drag->exec();
}
