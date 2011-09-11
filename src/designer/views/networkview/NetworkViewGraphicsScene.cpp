#include "NetworkViewGraphicsScene.h"
#include "NetworkViewGraphicsSceneNodeReaction.h"
#include "NetworkViewGraphicsSceneNodeSubstance.h"
#include "documents/MoDeL/MoDeLDocParser.h"
#include "models/common/ModelSymbol.h"
#include "DesignerDebug.h"

NetworkViewGraphicsScene::NetworkViewGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
    this->loaded=false;
    this->locked=false;
    this->idSpace=new QSet<QString>();
}

void NetworkViewGraphicsScene::clearScene()
{
    for(size_t i = items().count(); i > 0 ; i --)
    {
        delete items().at(i-1);
        items().removeAt(i-1);
    }
    this->idSpace->clear();
}

void NetworkViewGraphicsScene::addItem(QGraphicsItem *item)
{
    bool accept=true;
    if(dynamic_cast<NetworkViewGraphicsItem *>(item))
    {
        if(!dynamic_cast<NetworkViewGraphicsItem *>(item)->getId().isEmpty())
        {
            idSpace->insert(dynamic_cast<NetworkViewGraphicsItem *>(item)->getId());
        }       
        dynamic_cast<NetworkViewGraphicsItem *>(item)->setPositon();
        dynamic_cast<NetworkViewGraphicsItem *>(item)->registPos();
    }
    if( dynamic_cast<NetworkViewGraphicsSceneContainer *>(item))
    {
        foreach(QGraphicsItem *item_,items())
        {
            if( dynamic_cast<NetworkViewGraphicsSceneContainer *>(item_))
            {
                accept=false;
                break;
            }
        }
    }
    this->locked=true;
    if(!item->parentItem()&&accept)
        QGraphicsScene::addItem(item);    
    refreshScriptValue();
    this->clearSelection();
    this->locked=false;
    item->setSelected(true);
}

void NetworkViewGraphicsScene::removeItem( NetworkViewGraphicsItem * item )
{
    if( !item->getId().isEmpty() )
    {
        idSpace->remove(item->getId());
    }
    foreach( NetworkViewGraphicsItem * child , item->children) delete child;
    this->locked=true;
    QGraphicsScene::removeItem(item);
    refreshScriptValue();
    this->locked=false;
    if(items().count()==0)
        emit this->selectionChanged();
}

void NetworkViewGraphicsScene::loadFromModel(DesignerModelItf* model)
{
//    qDebug()<<model->getModel();
    this->clearScene();
    this->loaded=false;

    QScriptValue compartmentsArray = model->getModel().property("compartments");
    int compartmentsCount = compartmentsArray.property("length").toInt32();
    QMap<QString, NetworkViewGraphicsSceneContainer*> containerMap;

    for(int i=0;i<compartmentsCount;i++)
    {
        NetworkViewGraphicsSceneContainer* newContainer =
                new NetworkViewGraphicsSceneContainer(compartmentsArray.property(i),activePanel());       
        addItem(newContainer);        
        containerMap[compartmentsArray.property(i).property("id").toString()]=newContainer;
    }

    QScriptValue speciesArray = model->getModel().property("species");
    int speciesCount = speciesArray.property("length").toInt32();
    QMap<QString, NetworkViewGraphicsSceneNodeSubstance*> substanceMap;
    for(int i=0;i<speciesCount;i++)
    {
        QScriptValue parentCompartment = speciesArray.property(i).property("compartment");
        NetworkViewGraphicsSceneNodeSubstance* newNode;
        NetworkViewGraphicsSceneContainer* container;
        if(parentCompartment.isNull()||!(container = containerMap[parentCompartment.toString()]))
        {
            newNode = new NetworkViewGraphicsSceneNodeSubstance(speciesArray.property(i),activePanel());           
            addItem(newNode);
        }
        else
        {
            newNode = new NetworkViewGraphicsSceneNodeSubstance(speciesArray.property(i),container,true);
            this->addItem(newNode);
        }        

        substanceMap.insert(speciesArray.property(i).property("id").toString(), newNode);
    }

    QScriptValue reactionArray = model->getModel().property("reactions");
    int reactionCount = reactionArray.property("length").toInt32();
    for(int i=0;i<reactionCount;i++)
    {
        //  qDebug()<<reactionArray.property(i);
        //  judge if the reaction belongs to a certain compartment
        int reactantsCount = reactionArray.property(i).property("reactants").property("length").toInt32();
        int productsCount = reactionArray.property(i).property("products").property("length").toInt32();
        int modifiersCount = reactionArray.property(i).property("modifiers").property("length").toInt32();

        bool sameCompartment=true;
        QString sameCompartmentName;
        bool foundItem = false;
        for(int j=0;j<reactantsCount;j++)
        {
            NetworkViewGraphicsSceneNodeSubstance* substanceItem = substanceMap[reactionArray.property(i).property("reactants").property(j).property("species").toString()];
            QString compartmentName = "";
            if(substanceItem)
                compartmentName = substanceItem->itemObject.property("compartment").toString();
            if(!foundItem)
            {
                foundItem = true;
                sameCompartmentName = compartmentName;
            }
            if(sameCompartmentName!=compartmentName||!sameCompartment)
            {
                sameCompartment = false;
                break;
            }
        }
        for(int j=0;j<productsCount;j++)
        {
            NetworkViewGraphicsSceneNodeSubstance* substanceItem = substanceMap[reactionArray.property(i).property("products").property(j).property("species").toString()];
            QString compartmentName = "";
            if(substanceItem)
                compartmentName = substanceItem->itemObject.property("compartment").toString();
            if(!foundItem)
            {
                foundItem = true;
                sameCompartmentName = compartmentName;
            }
            if(sameCompartmentName!=compartmentName||!sameCompartment)
            {
                sameCompartment = false;
                break;
            }

        }

        NetworkViewGraphicsSceneContainer* container;
        NetworkViewGraphicsSceneNodeReaction* newNode;

        if(!sameCompartment)
        {
            newNode = new NetworkViewGraphicsSceneNodeReaction(reactionArray.property(i),activePanel());
            addItem(newNode);
        }
        else
        {
            container=containerMap[sameCompartmentName];
            newNode= new NetworkViewGraphicsSceneNodeReaction(reactionArray.property(i),container);
            this->addItem(newNode);
        }

        //reactants

        for(int j=0;j<reactantsCount;j++)
        {
            NetworkViewGraphicsSceneNodeSubstance* existingNode =
                    substanceMap[reactionArray.property(i).property("reactants").property(j).property("species").toString()];
            if(existingNode)
            {
                NetworkViewGraphicsSceneEdge* newEdge = new NetworkViewGraphicsSceneEdge(
                            activePanel(),existingNode, newNode, NetworkViewGraphicsSceneEdge::DirectedEdge);
                addItem(newEdge);
            }
        }

        //products
        for(int j=0;j<productsCount;j++)
        {
            NetworkViewGraphicsSceneNodeSubstance* existingNode =
                    substanceMap[reactionArray.property(i).property("products").property(j).property("species").toString()];
            if(existingNode)
            {
                NetworkViewGraphicsSceneEdge* newEdge = new NetworkViewGraphicsSceneEdge(
                            activePanel(),newNode, existingNode, NetworkViewGraphicsSceneEdge::DirectedEdge);
                addItem(newEdge);
            }
        }

        //modifiers
        for(int j=0;j<modifiersCount;j++)
        {
            NetworkViewGraphicsSceneNodeSubstance* existingNode =
                    substanceMap[reactionArray.property(i).property("modifiers").property(j).property("species").toString()];
            if(existingNode)
            {
                NetworkViewGraphicsSceneModification* newEdge = new NetworkViewGraphicsSceneModification(
                            activePanel(),existingNode, newNode);
                addItem(newEdge);
            }
        }
    }
    this->loaded=true;
}

void NetworkViewGraphicsScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Delete:
        foreach( QGraphicsItem * item , selectedItems() )
        {
            if( dynamic_cast<NetworkViewGraphicsItem*>(item))
                delete item;
        }
        break;
    default:
        QGraphicsScene::keyPressEvent(event);
        return;
    }
    event->accept();
}

void NetworkViewGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    event->acceptProposedAction();
}

void NetworkViewGraphicsScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    NetworkViewGraphicsItem * item = 0;
    if( event->mimeData()->hasFormat("compartment") )
    {
        QByteArray itemData = event->mimeData()->data( "compartment" );
        QScriptValue * scriptValue;
        memcpy( &scriptValue , itemData.data() , sizeof(scriptValue) );
        QString itemId = scriptValue->property("id").toString();
        QString stri;
        for( int i = 1 ; ; i++ )
        {
            stri.setNum(i);
            if( ! idSpace->contains(itemId+stri) ) break;
        }
        itemId +=stri;
        scriptValue->setProperty("id", QScriptValue(itemId) );
        scriptValue->setProperty("name", QScriptValue(itemId) );
        item = new NetworkViewGraphicsSceneContainer( *scriptValue );
    }else if( event->mimeData()->hasFormat( "reaction" ) )
    {
        QByteArray itemData = event->mimeData()->data( "reaction" );
        QScriptValue * scriptValue;
        memcpy( &scriptValue , itemData.data() , sizeof(scriptValue) );
        QString itemId = scriptValue->property("id").toString();
        QString stri;
        for( int i = 1 ; ; i++ )
        {
            stri.setNum(i);
            if( ! idSpace->contains(itemId+stri) ) break;
        }
        itemId +=stri;
        scriptValue->setProperty("id", QScriptValue(itemId) );
        scriptValue->setProperty("name", QScriptValue(itemId) );
        item = new NetworkViewGraphicsSceneNodeReaction( *scriptValue );
    }else if( event->mimeData()->hasFormat( "substance" ) )
    {
        QByteArray itemData = event->mimeData()->data( "substance" );
        QScriptValue * scriptValue;
        memcpy( &scriptValue , itemData.data() , sizeof(scriptValue) );
        QString itemId = scriptValue->property("id").toString();
        QString stri;
        for( int i = 1 ; ; i++ )
        {
            stri.setNum(i);
            if( ! idSpace->contains(itemId+stri) ) break;
        }
        itemId +=stri;
        scriptValue->setProperty("id", QScriptValue(itemId) );
        scriptValue->setProperty("name", QScriptValue(itemId) );
        item = new NetworkViewGraphicsSceneNodeSubstance( *scriptValue );
    }
    else{
        QGraphicsScene::dropEvent(event);
        return;
    }    
    this->addItem(item);
    item->setPos( event->scenePos().x() - item->pixmap().width()/2 , event->scenePos().y() - item->pixmap().height()/2 );
    if(dynamic_cast<NetworkViewGraphicsSceneNode *>(item))
        if(!item->detectEdge())
        {
            delete item;
            return;
        }
    event->accept();
    return;
}

void NetworkViewGraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->acceptProposedAction();
}

void NetworkViewGraphicsScene::refreshScriptValue()
{
    if(!this->loaded)
        return;
    QScriptValueList containers;
    QScriptValueList reactions;
    QScriptValueList substances;
    foreach( QGraphicsItem * item , items() )
    {

        if( dynamic_cast<NetworkViewGraphicsSceneContainer *>(item))
        {
            containers.push_back(dynamic_cast<NetworkViewGraphicsItem*>(item)->itemObject);
        }else if( dynamic_cast<NetworkViewGraphicsSceneNodeReaction *>(item))
        {
            dynamic_cast<NetworkViewGraphicsSceneNodeReaction *>(item)->refreshScriptValue();
            reactions.push_back(dynamic_cast<NetworkViewGraphicsItem*>(item)->itemObject);
        }
        else if(dynamic_cast<NetworkViewGraphicsSceneNodeSubstance *>(item))
        {
            substances.push_back(dynamic_cast<NetworkViewGraphicsItem*>(item)->itemObject);
        }
    }
    if(!model->getModel().isValid())
        model->getEngine()->globalObject().setProperty("model",model->getEngine()->newObject());
    model->getModel().setProperty( "reactions" , convertModelTypeToScriptValue(model->getEngine(),reactions));
    model->getModel().setProperty( "compartments" , convertModelTypeToScriptValue(model->getEngine(),containers));
    model->getModel().setProperty("species", convertModelTypeToScriptValue(model->getEngine(),substances));
}

void NetworkViewGraphicsScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if( event->modifiers() == Qt::ControlModifier )
    {
        if( event->delta() > 0 )
        {
            foreach( QGraphicsView * view , views() )
            {
                view->scale( 1.1 , 1.1 );
            }
            event->accept();
            return;
        }else
        {
            foreach( QGraphicsView * view , views() )
            {
                view->scale( 1/1.1 , 1/1.1 );
            }
            event->accept();
            return;
        }
    }
    QGraphicsScene::wheelEvent(event);
}

void NetworkViewGraphicsScene::emitsignal()
{
    emit selectionChanged();
}
