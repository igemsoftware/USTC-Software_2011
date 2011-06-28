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
    //QMessageBox::information( 0 , tr("drag") , tr("drag") );
    QByteArray itemData = name.toLocal8Bit();
    QMimeData * mimeData = new QMimeData;
    mimeData->setData( type , itemData );

    QDrag * drag = new QDrag(this);
    drag->setMimeData( mimeData );
    drag->setPixmap( *(new QPixmap( tr("D://iGame//GIT//lachesis//textpointer.png") ) ));

    drag->exec();
}
