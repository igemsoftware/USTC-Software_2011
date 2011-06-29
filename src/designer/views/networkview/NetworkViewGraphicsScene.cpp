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

    NetworkViewGraphicsSceneNode* newNode = new NetworkViewGraphicsSceneNode(activePanel());
    newNode->setPos(0, 0);
    addItem(newNode);
    NetworkViewGraphicsSceneNode* newNode2 = new NetworkViewGraphicsSceneNode(activePanel());
    newNode2->setPos(200,200);
    addItem(newNode2);
    NetworkViewGraphicsSceneNode* newNode3 = new NetworkViewGraphicsSceneNode(activePanel());
    newNode3->setPos(200,0);
    addItem(newNode3);
    NetworkViewGraphicsSceneNode* newNode4 = new NetworkViewGraphicsSceneNode(activePanel());
    newNode4->setPos(400,-200);
    addItem(newNode4);

    NetworkViewGraphicsSceneEdge* newEdge = new NetworkViewGraphicsSceneEdge(activePanel(),newNode, newNode2, NetworkViewGraphicsSceneEdge::BidirectedEdge);
    addItem(newEdge);
    NetworkViewGraphicsSceneEdge* newEdge2 = new NetworkViewGraphicsSceneEdge(activePanel(),newNode3, newNode2, NetworkViewGraphicsSceneEdge::BidirectedEdge);
    addItem(newEdge2);
    NetworkViewGraphicsSceneEdge* newEdge3 = new NetworkViewGraphicsSceneEdge(activePanel(),newNode3, newNode, NetworkViewGraphicsSceneEdge::BidirectedEdge);
    addItem(newEdge3);
    NetworkViewGraphicsSceneEdge* newEdge4 = new NetworkViewGraphicsSceneEdge(activePanel(),newNode3, newNode4, NetworkViewGraphicsSceneEdge::BidirectedEdge);
    addItem(newEdge4);
}
