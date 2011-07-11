#include <QtScript>

#include "DesignerDebug.h"
#include "DesignerModelItf.h"

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
    QScriptEngine *engine =  model->getEngine();

//    qDebug()<<engine->globalObject().property("*model*");
    QScriptValue compartmentsArray = engine->globalObject().property("*model*").property("*compartmentlist*");
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

    QScriptValue speciesArray = engine->globalObject().property("*model*").property("*specieslist*");
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

    QScriptValue reactionArray = engine->globalObject().property("*model*").property("*reactionlist*");
    int reactionCount = reactionArray.property("length").toInt32();
    for(int i=0;i<reactionCount;i++)
    {
//        qDebug()<<reactionArray.property(i);
        NetworkViewGraphicsSceneNodeReaction* newNode = new NetworkViewGraphicsSceneNodeReaction(activePanel(), reactionArray.property(i));
        addItem(newNode);
        newNode->setLabel(reactionArray.property(i).property("id").toString());
        newNode->setPos(((double)rand()/RAND_MAX-0.5)*500,((double)rand()/RAND_MAX-0.5)*500);

        //reactants
        int reactantsCount = reactionArray.property(i).property("reactants").property("length").toInt32();
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
        int productsCount = reactionArray.property(i).property("products").property("length").toInt32();
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
