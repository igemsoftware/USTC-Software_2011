#include "AssemblyScene.h"

AssemblyScene::AssemblyScene(QObject *parent) :
    QGraphicsScene(parent)
{
}

void AssemblyScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if( event->mimeData()->hasFormat( AssemblyItemCompartment::MimeFormat ) )
    {
        event->acceptProposedAction();
    }else if( event->mimeData()->hasFormat( AssemblyItemPlasmid::MimeFormat ) )
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
    }else
    {
        QGraphicsScene::dragEnterEvent(event);
    }
}

void AssemblyScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if( event->mimeData()->hasFormat( AssemblyItemCompartment::MimeFormat ) )
    {
        QByteArray itemData = event->mimeData()->data( AssemblyItemCompartment::MimeFormat );
        QString itemName = QString::fromLocal8Bit( itemData.data() );
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
            QString itemName = QString::fromLocal8Bit( itemData.data() );
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

    QGraphicsScene::dropEvent(event);
}


































/*
void AssemblyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
}

void AssemblyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}

void AssemblyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
}*/
