#include <QtScript>

#include "DesignerDebug.h"
#include "interfaces/DesignerModelItf.h"

#include "NetworkViewGraphicsScene.h"
#include "NetworkViewGraphicsSceneContainer.h"
#include "NetworkViewGraphicsSceneEdge.h"
#include "NetworkViewGraphicsSceneNodeReaction.h"
#include "NetworkViewGraphicsSceneNodeSubstance.h"
#include "QKeyEvent"
#include <QList>
#include <QMessageBox>
NetworkViewGraphicsScene::NetworkViewGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{

}

void NetworkViewGraphicsScene::clearScene()
{
    for(size_t i = items().count(); i > 0 ; i --)
    {
        delete items().at(i-1);
        items().removeAt(i-1);
    }
}

void NetworkViewGraphicsScene::loadFromModel(DesignerModelItf* model)
{
//    qDebug()<<model->getModel();
    QScriptValue compartmentsArray = model->getModel().property("compartments");
    int compartmentsCount = compartmentsArray.property("length").toInt32();
    QMap<QString, NetworkViewGraphicsSceneContainer*> containerMap;

    for(int i=0;i<compartmentsCount;i++)
    {
        NetworkViewGraphicsSceneContainer* newContainer =
                new NetworkViewGraphicsSceneContainer(activePanel(),compartmentsArray.property(i));
        addItem(newContainer);
        //newContainer->setLabel(compartmentsArray.property(i).property("id").toString());
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
            newNode = new NetworkViewGraphicsSceneNodeSubstance(activePanel(), speciesArray.property(i));
            addItem(newNode);
            newNode->setPos(((double)rand()/RAND_MAX-0.5)*500+400,((double)rand()/RAND_MAX-0.5)*500+200);
        }
        else
        {
            newNode = new NetworkViewGraphicsSceneNodeSubstance(container, speciesArray.property(i), true);
            newNode->setPos(((double)rand()/RAND_MAX-0.5)*container->radius*2+400,((double)rand()/RAND_MAX-0.5)*container->radius*2+200);
        }
        //newNode->setLabel(speciesArray.property(i).property("id").toString());

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
            newNode = new NetworkViewGraphicsSceneNodeReaction(activePanel(), reactionArray.property(i));
            addItem(newNode);
            //newNode->setLabel(reactionArray.property(i).property("id").toString());
            newNode->setPos(((double)rand()/RAND_MAX-0.5)*500+400,((double)rand()/RAND_MAX-0.5)*500+200);
        }
        else
        {
            container=containerMap[sameCompartmentName];
            newNode= new NetworkViewGraphicsSceneNodeReaction(container, reactionArray.property(i));
            //newNode->setLabel(reactionArray.property(i).property("id").toString());
            newNode->setPos(((double)rand()/RAND_MAX-0.5)*container->radius*2+400,((double)rand()/RAND_MAX-0.5)*container->radius*2+200);
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

    }

}

void NetworkViewGraphicsScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Delete:
        foreach( QGraphicsItem * item , selectedItems() )
        {
            if(dynamic_cast<NetworkViewGraphicsSceneContainer*>(item))
               dynamic_cast<NetworkViewGraphicsSceneContainer*>(item)->deleteNodes();
            if(dynamic_cast<NetworkViewGraphicsSceneNode*>(item))
            {
                dynamic_cast<NetworkViewGraphicsSceneNode*>(item)->deleteEdges();
                if(dynamic_cast<NetworkViewGraphicsSceneNode*>(item)->parentItem()!=0&&dynamic_cast<NetworkViewGraphicsSceneContainer*>(dynamic_cast<NetworkViewGraphicsSceneNode*>(item)->parentItem()))
                    dynamic_cast<NetworkViewGraphicsSceneContainer*>(dynamic_cast<NetworkViewGraphicsSceneNode*>(item)->parentItem())->removeChild(dynamic_cast<NetworkViewGraphicsItem*>(item));
//                QMessageBox *qmb=new QMessageBox();
//                qmb->setText(QString::number(dynamic_cast<NetworkViewGraphicsSceneContainer*>(dynamic_cast<NetworkViewGraphicsSceneNode*>(item)->parent)->nodeList.count()));
//                qmb->exec();
            }
            if( dynamic_cast<NetworkViewGraphicsItem*>(item) )
                delete item;
        }
        break;
    default:
        QGraphicsScene::keyPressEvent(event);
        return;
    }
    event->accept();
}
