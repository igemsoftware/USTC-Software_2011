#include "AssemblyScene.h"
#include <QGraphicsView>
#include <QKeyEvent>

AssemblyScene::AssemblyScene(QObject *parent) :
    QGraphicsScene(parent)
{
    connect( this , SIGNAL(selectionChanged()) , this , SLOT(selectionMessage()) );
}

void AssemblyScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if( event->mimeData()->hasFormat( AssemblyItemCompartment::MimeFormat ) )
    {
        event->acceptProposedAction();
    }else if( event->mimeData()->hasFormat( AssemblyItemPlasmid::MimeFormat ) )
    {
        event->acceptProposedAction();
    }else if ( event->mimeData()->hasFormat( AssemblyItemBrick::MimeFormat ) )
    {
        event->acceptProposedAction();
    }else
    {
        QGraphicsScene::dragEnterEvent(event);
    }
}

void AssemblyScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if( event->mimeData()->hasFormat( AssemblyItemCompartment::MimeFormat ) )
    {
        event->acceptProposedAction();
    }else if( event->mimeData()->hasFormat( AssemblyItemPlasmid::MimeFormat ) )
    {
        event->acceptProposedAction();
    }else if ( event->mimeData()->hasFormat( AssemblyItemBrick::MimeFormat ) )
    {
        event->acceptProposedAction();
    }else
    {
        QGraphicsScene::dragMoveEvent(event);
    }
}

void AssemblyScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if( event->mimeData()->hasFormat( AssemblyItemCompartment::MimeFormat ) )
    {
        QByteArray itemData = event->mimeData()->data( AssemblyItemCompartment::MimeFormat );
        QString itemName = QString::fromUtf8( itemData.data() );
        QString stri;
        for( int i = 1 ; ; i++ )
        {
            stri.setNum(i);
            if( ! compartmentMap.contains(itemName+stri) ) break;
        }
        itemName += stri;
        AssemblyItemCompartment * item = new AssemblyItemCompartment( itemName );
        compartmentMap.insert( itemName , item );
        item->setPos( event->scenePos().x() - item->rect().width()/2 , event->scenePos().y() - item->rect().height()/2 );
        addItem(item);

        return;
    }

    if( event->mimeData()->hasFormat( AssemblyItemPlasmid::MimeFormat ) )
    {
        AssemblyItemCompartment * compartment = 0;
        QList<QGraphicsItem*> itemList = items( event->scenePos() , Qt::IntersectsItemShape , Qt::DescendingOrder );
        for( QList<QGraphicsItem*>::iterator iter = itemList.begin() ; iter != itemList.end() ; iter++ )
        {
            if( dynamic_cast<AssemblyItemCompartment*>(*iter) != 0 )
            {
                compartment = dynamic_cast<AssemblyItemCompartment*>(*iter);
                break;
            }
        }
        if( compartment )
        {
            QByteArray itemData = event->mimeData()->data( AssemblyItemPlasmid::MimeFormat );
            QString itemName = QString::fromUtf8( itemData.data() );
            QString stri;
            for( int i = 1 ; ; i++ )
            {
                stri.setNum(i);
                if( ! plasmidMap.contains(itemName+stri) ) break;
            }
            itemName += stri;
            AssemblyItemPlasmid * item = new AssemblyItemPlasmid( itemName );
            plasmidMap.insert( itemName , item );
            compartment->addPlasmid( event->scenePos() , item );

            return;
        }
    }

    if( event->mimeData()->hasFormat( AssemblyItemBrick::MimeFormat ) )
    {
        AssemblyItemPlasmid * plasmid = 0;
        QList<QGraphicsItem*> itemList = items( event->scenePos() , Qt::IntersectsItemShape , Qt::DescendingOrder );
        for( QList<QGraphicsItem*>::iterator iter = itemList.begin() ; iter != itemList.end() ; iter++ )
        {
            if( dynamic_cast<AssemblyItemPlasmid*>(*iter) != 0 )
            {
                plasmid = dynamic_cast<AssemblyItemPlasmid*>(*iter);
                break;
            }
        }
        if( plasmid )
        {
            QByteArray itemData = event->mimeData()->data( AssemblyItemBrick::MimeFormat );
            QString itemName = QString::fromUtf8( itemData.data() );

            AssemblyItemBrick * item = new AssemblyItemBrick( itemName );
            plasmid->addBrick( event->scenePos() , item );

            return;
        }
    }

    QGraphicsScene::dropEvent(event);
}

void AssemblyScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if( event->modifiers() == Qt::ControlModifier )
    {
        if( event->delta() > 0 )
        {
            foreach( QGraphicsView * view , views() )
            {
                view->scale( 1.2 , 1.2 );
            }
            return;
        }else
        {
            foreach( QGraphicsView * view , views() )
            {
                view->scale( 1/1.2 , 1/1.2 );
            }
            return;
        }
    }
    QGraphicsScene::wheelEvent(event);
}

void AssemblyScene::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_Delete )
    {
        foreach( QGraphicsItem * item , selectedItems() )
        {
            if( dynamic_cast<AssemblyItemBrick*>(item) || dynamic_cast<AssemblyItemPlasmid*>(item) || dynamic_cast<AssemblyItemCompartment*>(item) )
                delete item;
        }
    }
}

void AssemblyScene::removeItem(QGraphicsItem *item)
{
    if( dynamic_cast<AssemblyItemPlasmid*>(item) != 0 )
    {
        plasmidMap.remove( dynamic_cast<AssemblyItemPlasmid*>(item)->name );
    }
    if( dynamic_cast<AssemblyItemCompartment*>(item) != 0 )
    {
        compartmentMap.remove( dynamic_cast<AssemblyItemCompartment*>(item)->name );
    }
    QGraphicsScene::removeItem(item);
}

void AssemblyScene::selectionMessage()
{
    foreach( QGraphicsItem * item , previousSelection )
    {
        if( dynamic_cast<AssemblyItemCompartment*>(item) != 0 )
        {
            dynamic_cast<AssemblyItemCompartment*>(item)->loseSelection();
        }
    }
    previousSelection = selectedItems();
    foreach( QGraphicsItem * item , previousSelection )
    {
        if( dynamic_cast<AssemblyItemCompartment*>(item) != 0 )
        {
            dynamic_cast<AssemblyItemCompartment*>(item)->getSelection();
        }
    }
}





















