#include "NetworkViewGraphicsSceneContainer.h"
#include "NetworkViewGraphicsSceneNode.h"
#include "NetworkViewGraphicsSceneEdge.h"
#include "NetworkViewGraphicsSceneLabel.h"

NetworkViewGraphicsSceneNode::NetworkViewGraphicsSceneNode(QGraphicsItem *parent, QScriptValue value, bool isParentContainer)
    : QGraphicsEllipseItem(-radius, -radius, radius*2, radius*2, parent),
      NetworkViewGraphicsItem(value)
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
    return QGraphicsEllipseItem::itemChange(change, value);
}

void NetworkViewGraphicsSceneNode::setLabel(QString label)
{
    labelObject->setPlainText(label);
}
