#include "NetworkViewGraphicsSceneNode.h"

NetworkViewGraphicsSceneNode::NetworkViewGraphicsSceneNode(QGraphicsItem *parent, QScriptValue value ,QString normalImagePath , QString selectedImagePath , bool isParentContainer)
    : NetworkViewGraphicsItem( value , normalImagePath , selectedImagePath , parent )
{
    setFlags( QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsSelectable | ItemSendsGeometryChanges);
    if(dynamic_cast<NetworkViewGraphicsItem*>(parent))dynamic_cast<NetworkViewGraphicsItem*>(parent)->addChild(scenePos(),this);
    setZValue(1);
}

NetworkViewGraphicsSceneNode::~NetworkViewGraphicsSceneNode()
{
    this->deleteEdgesAndMods();
}

void NetworkViewGraphicsSceneNode::registerEdge(NetworkViewGraphicsSceneEdge* edge)
{
    if(edge && edgeList.indexOf(edge)==-1) edgeList.append(edge);
}

void NetworkViewGraphicsSceneNode::registerMod(NetworkViewGraphicsSceneModification *mod)
{
    if(mod && modList.indexOf(mod)==-1) modList.append(mod);
}

void NetworkViewGraphicsSceneNode::updatePos()
{
    for(size_t i = edgeList.count(); i > 0; i--)
    {
        edgeList[i-1]->updatePos();
    }
    for(size_t i = modList.count(); i > 0; i--)
    {
        modList[i-1]->updatePos();
    }
}

QVariant NetworkViewGraphicsSceneNode::itemChange(GraphicsItemChange change, const QVariant& value)
{
    if (change == ItemPositionHasChanged && scene()) {
        updatePos();
    }
    return NetworkViewGraphicsItem::itemChange(change, value);
}

void NetworkViewGraphicsSceneNode::deleteEdgesAndMods()
{
    while(this->edgeList.count()!=0)
        delete edgeList[0];
    while(this->modList.count()!=0)
        delete modList[0];
    this->edgeList.clear();
    this->modList.clear();
}

void NetworkViewGraphicsSceneNode::deleteEdge(NetworkViewGraphicsSceneEdge *edge)
{
    for(int i=0;i<this->edgeList.count();i++)
    {
        if(edge==edgeList[i])
           this->edgeList.removeAt(i);
    }
}

void NetworkViewGraphicsSceneNode::deleteMod(NetworkViewGraphicsSceneModification *mod)
{
    for(int i=0;i<this->modList.count();i++)
    {
        if(mod==modList[i])
           this->modList.removeAt(i);
    }
}
