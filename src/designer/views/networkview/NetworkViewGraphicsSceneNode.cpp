#include "NetworkViewGraphicsSceneContainer.h"
#include "NetworkViewGraphicsSceneNode.h"
#include "NetworkViewGraphicsSceneEdge.h"
#include "NetworkViewGraphicsSceneLabel.h"

NetworkViewGraphicsSceneNode::NetworkViewGraphicsSceneNode(QGraphicsItem *parent, QScriptValue value ,QString normalImagePath , QString selectedImagePath , bool isParentContainer)
    : NetworkViewGraphicsItem( value , normalImagePath , selectedImagePath , parent )
{
    setFlags( QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsSelectable | ItemSendsGeometryChanges);
    labelObject = new NetworkViewGraphicsSceneLabel(this);

    if(isParentContainer)
    {
        dynamic_cast<NetworkViewGraphicsSceneContainer*>(parent)->registerNode(this);
    }
}


void NetworkViewGraphicsSceneNode::registerEdge(NetworkViewGraphicsSceneEdge* edge)
{
    if(edge && edgeList.indexOf(edge)==-1) edgeList.append(edge);
}

void NetworkViewGraphicsSceneNode::updatePos()
{
    for(size_t i = edgeList.count(); i > 0; i--)
    {
        edgeList[i-1]->updatePos();
    }
}

QVariant NetworkViewGraphicsSceneNode::itemChange(GraphicsItemChange change, const QVariant& value)
{
    if (change == ItemPositionHasChanged && scene()) {
        updatePos();
    }
    return NetworkViewGraphicsItem::itemChange(change, value);
}

void NetworkViewGraphicsSceneNode::setLabel(QString label)
{
    labelObject->setPlainText(label);
}

void NetworkViewGraphicsSceneNode::deleteEdge()
{
    for(int i=0;i<this->edgeList.count();i++)
        delete this->edgeList[i];
}
