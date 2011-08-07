#include "AssemblyScene.h"
#include <QGraphicsView>
#include <QKeyEvent>

AssemblyScene::AssemblyScene( IGameModel * newModel , QObject *parent) :
    QGraphicsScene(parent) , model(newModel)
{
    connect( this , SIGNAL(selectionChanged()) , this , SLOT(propagateSelectionChange()) );
    if( model->getEngine()->globalObject().property("model").isObject() )
    {
        QScriptValue root = model->getEngine()->globalObject().property("model");
        QScriptValue rootCompartment = root.property("rootCompartment");

        if( rootCompartment.property("contains").isArray() )
        {
            QScriptValueList children;
            qScriptValueToSequence( rootCompartment.property("contains") , children );
            foreach( QScriptValue child , children )
            {
                if( child.property("type").toString() == "plasmid" )
                {
                    AssemblyItemPlasmid * plasmid = new AssemblyItemPlasmid(child);
                    QGraphicsScene::addItem( plasmid );
                    if( !registerItem( plasmid ) )
                    {
                        delete plasmid;
                    }
                }else if( child.property("type").toString() == "protein" || child.property("type").toString() == "molecule" )
                {
                    AssemblyItemMolecule * molecule = new AssemblyItemMolecule(child);
                    QGraphicsScene::addItem( molecule );
                    if( !registerItem( molecule ) )
                    {
                        delete molecule;
                    }
                }
            }
        }
        QScriptValueList childCompartments;
        qScriptValueToSequence( root.property("childCompartments") , childCompartments );
        foreach( QScriptValue child , childCompartments )
        {
            AssemblyItemCompartment * compartment = new AssemblyItemCompartment( child );
            QGraphicsScene::addItem( compartment );
            if( !registerItem( compartment ) )
            {
                delete compartment;
            }
        }
    }else{
        QScriptValue root , rootCompartment;
        model->getEngine()->globalObject().setProperty("model", root = model->getEngine()->newObject() );
        root.setProperty( "parameters" , model->getEngine()->newArray() );
        root.setProperty( "events" , model->getEngine()->newArray() );
        root.setProperty( "rootCompartment" , rootCompartment = model->getEngine()->newObject() );
        rootCompartment.setProperty( "id" , "flask" );
        rootCompartment.setProperty( "type" , "flask" );
        rootCompartment.setProperty( "contains" , model->getEngine()->newArray() );
    }
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
    }else if ( event->mimeData()->hasFormat( AssemblyItemMolecule::MimeFormat ) )
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
    }else if ( event->mimeData()->hasFormat( AssemblyItemMolecule::MimeFormat ) )
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
        QString itemId = scriptValue->property("id").toString();
        QString stri;
        for( int i = 1 ; ; i++ )
        {
            stri.setNum(i);
            if( ! childrenMap.contains(itemId+stri) ) break;
        }
        itemId += stri;
        scriptValue->setProperty("id", QScriptValue(itemId) );
        item = new AssemblyItemCompartment( *scriptValue );
    }else if( event->mimeData()->hasFormat( AssemblyItemPlasmid::MimeFormat ) )
    {
        QByteArray itemData = event->mimeData()->data( AssemblyItemPlasmid::MimeFormat );
        QScriptValue * scriptValue;
        memcpy( &scriptValue , itemData.data() , sizeof(scriptValue) );
        QString itemId = scriptValue->property("id").toString();
        QString stri;
        for( int i = 1 ; ; i++ )
        {
            stri.setNum(i);
            if( ! childrenMap.contains(itemId+stri) ) break;
        }
        itemId += stri;
        scriptValue->setProperty("id", QScriptValue(itemId) );
        item = new AssemblyItemPlasmid( *scriptValue );
    }else if( event->mimeData()->hasFormat( AssemblyItemMolecule::MimeFormat ) )
    {
        QByteArray itemData = event->mimeData()->data( AssemblyItemMolecule::MimeFormat );
        QScriptValue * scriptValue;
        memcpy( &scriptValue , itemData.data() , sizeof(scriptValue) );
        QString itemId = scriptValue->property("id").toString();
        QString stri;
        for( int i = 1 ; ; i++ )
        {
            stri.setNum(i);
            if( ! childrenMap.contains(itemId+stri) ) break;
        }
        itemId += stri;
        scriptValue->setProperty("id", QScriptValue(itemId) );
        item = new AssemblyItemMolecule( *scriptValue );
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
    if( !item->getId().isEmpty() ) childrenMap.remove( item->getId() );
    foreach( AssemblyItemBase * child , item->getChildren() ) removeItem(child);
    QGraphicsScene::removeItem(item);
}

bool AssemblyScene::registerItem(AssemblyItemBase *item)
{
    QString id = item->getId();
    if( id.isEmpty() ) return true;
    if( !childrenMap.contains(id) )
    {
        childrenMap.insert(id,item);
        foreach( AssemblyItemBase * childItem , item->getChildren() ) registerItem(childItem);
        return true;
    }else{
        QGraphicsScene::removeItem(item);
        return false;
    }
}

bool AssemblyScene::addItem(AssemblyItemBase *item,bool flag)
{
    if( item->scene() != this ) QGraphicsScene::addItem(item);
    QList<QGraphicsItem*> candidates = collidingItems( item );
    foreach( QGraphicsItem * candidate , candidates )
    {
        if( dynamic_cast<AssemblyItemBase*>(candidate) && dynamic_cast<AssemblyItemBase*>(candidate)->addChild( item->scenePos() , item ) )
        {
            if( flag ) registerItem( item );
            foreach( QGraphicsItem* item , selectedItems() )
            {
                if( dynamic_cast<AssemblyItemBase*>(item) )
                {
                    emit setScriptValue(dynamic_cast<AssemblyItemBase*>(item)->getScriptValue());
                }
            }
            return true;
        }
    }

    if( dynamic_cast<AssemblyItemCompartment*>(item) || dynamic_cast<AssemblyItemMolecule*>(item) || dynamic_cast<AssemblyItemPlasmid*>(item) )
    {
        if( flag ) registerItem( item );
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
        if( dynamic_cast<AssemblyItemBase*>(item) )
        {
            dynamic_cast<AssemblyItemBase*>(item)->getSelection();
            emit setScriptValue(dynamic_cast<AssemblyItemBase*>(item)->getScriptValue());
        }
    }
}
















