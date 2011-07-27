#include <QtScript>

#include "DesignerDebug.h"
#include "interfaces/DesignerModelItf.h"

#include "NetworkViewGraphicsScene.h"
#include "NetworkViewGraphicsSceneContainer.h"
#include "NetworkViewGraphicsSceneEdge.h"
#include "NetworkViewGraphicsSceneNodeReaction.h"
#include "NetworkViewGraphicsSceneNodeSubstance.h"

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
        newContainer->itemObject = compartmentsArray.property(i);
        containerMap[compartmentsArray.property(i).property("id").toString()]=newContainer;
    }

    QScriptValue speciesArray = model->getModel().property("species");
    int speciesCount = speciesArray.property("length").toInt32();
    QMap<QString, NetworkViewGraphicsSceneNodeSubstance*> substanceMap;
    for(int i=0;i<speciesCount;i++)
    {
//        qDebug()<<speciesArray.property(i);
        QScriptValue parentCompartment = speciesArray.property(i).property("compartment");
        NetworkViewGraphicsSceneNodeSubstance* newNode;
        NetworkViewGraphicsSceneContainer* container;
        if(parentCompartment.isNull()||!(container = containerMap[parentCompartment.toString()]))
        {
            newNode = new NetworkViewGraphicsSceneNodeSubstance(activePanel(), speciesArray.property(i));
            addItem(newNode);
            newNode->setPos(((double)rand()/RAND_MAX-0.5)*500,((double)rand()/RAND_MAX-0.5)*500);
        }
        else
        {
            newNode = new NetworkViewGraphicsSceneNodeSubstance(container, speciesArray.property(i), true);
            newNode->setPos(((double)rand()/RAND_MAX-0.5)*container->radius*2,((double)rand()/RAND_MAX-0.5)*container->radius*2);
        }
        newNode->setLabel(speciesArray.property(i).property("id").toString());

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
        bool judge=true;
        QString tmpCompartment=NULL;
        for(int j=0;j<reactantsCount;j++)
        {
            QScriptValue parentCompartment = reactionArray.property(i).property("reactants").property(j).property("compartment");
            if(parentCompartment.isNull())
            {
                judge=false;
                break;
            }
            else if(tmpCompartment.isNull())
                tmpCompartment=parentCompartment.toString();
            if(parentCompartment.toString()!=tmpCompartment)
            {
                judge=false;
                break;
            }
        }
        for(int j=0;j<productsCount;j++)
        {
            QScriptValue parentCompartment = reactionArray.property(i).property("products").property(j).property("compartment");
            if(parentCompartment.isNull())
            {
                judge=false;
                break;
            }
            else if(tmpCompartment.isNull())
                tmpCompartment=parentCompartment.property("id").toString();
            if(parentCompartment.property("id").toString()!=tmpCompartment)
            {
                judge=false;
                break;
            }
        }

        NetworkViewGraphicsSceneContainer* container;
        NetworkViewGraphicsSceneNodeReaction* newNode;

        if(!judge)
        {
            newNode = new NetworkViewGraphicsSceneNodeReaction(activePanel(), reactionArray.property(i));
            addItem(newNode);
            newNode->setLabel(reactionArray.property(i).property("id").toString());
            newNode->setPos(((double)rand()/RAND_MAX-0.5)*500,((double)rand()/RAND_MAX-0.5)*500);
        }
        else
        {
            container=containerMap[tmpCompartment];
            newNode= new NetworkViewGraphicsSceneNodeReaction(container, reactionArray.property(i));
            addItem(newNode);
            newNode->setLabel(reactionArray.property(i).property("id").toString());
            newNode->setPos(((double)rand()/RAND_MAX-0.5)*container->radius*2,((double)rand()/RAND_MAX-0.5)*container->radius*2);
        }

        //reactants

        for(int j=0;j<reactantsCount;j++)
        {
            NetworkViewGraphicsSceneNodeSubstance* existingNode =
                    substanceMap[reactionArray.property(i).property("reactants").property(j).toString()];
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
                    substanceMap[reactionArray.property(i).property("products").property(j).toString()];
            if(existingNode)
            {
                NetworkViewGraphicsSceneEdge* newEdge = new NetworkViewGraphicsSceneEdge(
                            activePanel(),newNode, existingNode, NetworkViewGraphicsSceneEdge::DirectedEdge);
                addItem(newEdge);
            }
        }

    }

}
