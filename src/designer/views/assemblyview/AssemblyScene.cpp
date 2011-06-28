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
    }else
        QGraphicsScene::dragEnterEvent(event);

}

void AssemblyScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if( event->mimeData()->hasFormat( AssemblyItemCompartment::MimeFormat ) )
    {
        QByteArray itemData = event->mimeData()->data( AssemblyItemCompartment::MimeFormat );
        QString itemName;
        itemName.fromLocal8Bit( itemData.data() );
        AssemblyItemCompartment * item = new AssemblyItemCompartment( itemName );
        item->setPos( event->scenePos().x() - item->rect().width()/2 , event->scenePos().y() - item->rect().height()/2 );
        addItem(item);

    }else
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
