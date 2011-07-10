#include <QtScript>

#include "DesignerDebug.h"
#include "DesignerModelItf.h"

#include "NetworkViewGraphicsScene.h"
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

//    qDebug()<<engine->globalObject();
    QScriptValue speciesArray = engine->globalObject().property("*model*").property("*specieslist*");
    int speciesCount = speciesArray.property("length").toInt32();

    QMap<QString, NetworkViewGraphicsSceneNodeSubstance*> substanceMap;
    for(int i=0;i<speciesCount;i++)
    {
//        qDebug()<<speciesArray.property(i);
        NetworkViewGraphicsSceneNodeSubstance* newNode = new NetworkViewGraphicsSceneNodeSubstance(activePanel());
        addItem(newNode);
        newNode->setLabel(speciesArray.property(i).property("id").toString());
        newNode->setPos(((double)rand()/RAND_MAX-0.5)*500,((double)rand()/RAND_MAX-0.5)*500);

        substanceMap.insert(speciesArray.property(i).property("id").toString(), newNode);
    }

    QScriptValue reactionArray = engine->globalObject().property("*model*").property("*reactionlist*");
    int reactionCount = reactionArray.property("length").toInt32();
    for(int i=0;i<reactionCount;i++)
    {
//        qDebug()<<reactionArray.property(i);
        NetworkViewGraphicsSceneNodeReaction* newNode = new NetworkViewGraphicsSceneNodeReaction(activePanel());
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
