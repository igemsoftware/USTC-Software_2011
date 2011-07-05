#include "AssemblyScene.h"
#include <QGraphicsView>
#include <QKeyEvent>

AssemblyScene::AssemblyScene(QObject *parent) :
    QGraphicsScene(parent)
{
    connect( this , SIGNAL(selectionChanged()) , this , SLOT(propagateSelectionChange()) );
}

void AssemblyScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if( event->mimeData()->hasFormat( AssemblyItemCompartment::MimeFormat ) )
    {
        event->acceptProposedAction();
    }else if( event->mimeData()->hasFormat( AssemblyItemPlasmid::MimeFormat ) )
    {
        event->acceptProposedAction();
    }else if ( event->mimeData()->hasFormat( AssemblyItemPart::MimeFormat ) )
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
    }else if ( event->mimeData()->hasFormat( AssemblyItemPart::MimeFormat ) )
    {
        event->acceptProposedAction();
    }else
    {
        QGraphicsScene::dragMoveEvent(event);
    }
}

void AssemblyScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    AssemblyItemBase * item = 0;
    if( event->mimeData()->hasFormat( AssemblyItemCompartment::MimeFormat ) )
    {
        QByteArray itemData = event->mimeData()->data( AssemblyItemCompartment::MimeFormat );
        QScriptValue * scriptValue;
        memcpy( &scriptValue , itemData.data() , sizeof(scriptValue) );
        QString itemName = scriptValue->property("name").toString();
        QString stri;
        for( int i = 1 ; ; i++ )
        {
            stri.setNum(i);
            if( ! childrenMap.contains(itemName+stri) ) break;
        }
        itemName += stri;
        scriptValue->setProperty("name", QScriptValue(itemName) );
        item = new AssemblyItemCompartment( *scriptValue );
    }else if( event->mimeData()->hasFormat( AssemblyItemPlasmid::MimeFormat ) )
    {
        QByteArray itemData = event->mimeData()->data( AssemblyItemPlasmid::MimeFormat );
        QScriptValue * scriptValue;
        memcpy( &scriptValue , itemData.data() , sizeof(scriptValue) );
        QString itemName = scriptValue->property("name").toString();
        QString stri;
        for( int i = 1 ; ; i++ )
        {
            stri.setNum(i);
            if( ! childrenMap.contains(itemName+stri) ) break;
        }
        itemName += stri;
        scriptValue->setProperty("name", QScriptValue(itemName) );
        item = new AssemblyItemPlasmid( *scriptValue );
    }else if( event->mimeData()->hasFormat( AssemblyItemPart::MimeFormat ) )
    {
        QByteArray itemData = event->mimeData()->data( AssemblyItemPart::MimeFormat );
        QScriptValue * scriptValue;
        memcpy( &scriptValue , itemData.data() , sizeof(scriptValue) );
        item = new AssemblyItemPart( *scriptValue );
    }else{
        QGraphicsScene::dropEvent(event);
        return;
    }
    item->setPos( event->scenePos().x() - item->pixmap().width()/2 , event->scenePos().y() - item->pixmap().height()/2 );

    if( addItem( item ) )
    {
        event->accept();
    }else{
        QGraphicsScene::dropEvent(event);
    }
    return;
}

void AssemblyScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if( event->modifiers() == Qt::ControlModifier )
    {
        if( event->delta() > 0 )
        {
            foreach( QGraphicsView * view , views() )
            {
                view->scale( 1.1 , 1.1 );
            }
            return;
        }else
        {
            foreach( QGraphicsView * view , views() )
            {
                view->scale( 1/1.1 , 1/1.1 );
            }
            return;
        }
    }
    QGraphicsScene::wheelEvent(event);
}

void AssemblyScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key() )
    {
    case Qt::Key_Delete:
        foreach( QGraphicsItem * item , selectedItems() )
        {
            if( dynamic_cast<AssemblyItemBase*>(item) )
                delete item;
        }
        break;
    default:
        QGraphicsScene::keyPressEvent(event);
        return;
    }
    event->accept();
}

void AssemblyScene::removeItem( AssemblyItemBase * item )
{
    childrenMap.remove( item->getName() );
    foreach( AssemblyItemBase * child , item->getChildren() ) removeItem(child);
    QGraphicsScene::removeItem(item);
}


bool AssemblyScene::addItem(AssemblyItemBase *item)
{
    if( item->scene() != this ) QGraphicsScene::addItem(item);
    QList<QGraphicsItem*> candidates = collidingItems( item );
    foreach( QGraphicsItem * candidate , candidates )
    {
        if( dynamic_cast<AssemblyItemBase*>(candidate) && dynamic_cast<AssemblyItemBase*>(candidate)->addChild( item->scenePos() , item ) )
        {
            if( !dynamic_cast<AssemblyItemPart*>(item) ) childrenMap.insert( item->getName() , item );
            return true;
        }
    }
    if( dynamic_cast<AssemblyItemCompartment*>(item) )
    {
        if( !dynamic_cast<AssemblyItemPart*>(item) ) childrenMap.insert( item->getName() , item );
        return true;
    }
    delete item;
    return false;
}

void AssemblyScene::propagateSelectionChange()
{
    QList<QGraphicsItem*> newSelection = selectedItems();
    foreach( QGraphicsItem* item , items() )
    {
        if( dynamic_cast<AssemblyItemBase*>(item) ) dynamic_cast<AssemblyItemBase*>(item)->loseSelection(newSelection);
    }
    foreach( QGraphicsItem* item , newSelection )
    {
        if( dynamic_cast<AssemblyItemBase*>(item) ) dynamic_cast<AssemblyItemBase*>(item)->getSelection();
    }
}
















