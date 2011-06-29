#include "NetworkViewGraphicsSceneNode.h"
#include "NetworkViewGraphicsSceneEdge.h"
#include "NetworkViewGraphicsSceneLabel.h"

NetworkViewGraphicsSceneNode::NetworkViewGraphicsSceneNode(QGraphicsItem *parent)
    : QGraphicsEllipseItem(-radius, -radius, radius*2, radius*2, parent)
{
    setFlags( QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsSelectable | ItemSendsGeometryChanges);
    NetworkViewGraphicsSceneLabel *label = new NetworkViewGraphicsSceneLabel(this);

}


void NetworkViewGraphicsSceneNode::registerEdge(NetworkViewGraphicsSceneEdge* edge)
{
    if(edge && edgeList.indexOf(edge)==-1) edgeList.append(edge);
}

QVariant NetworkViewGraphicsSceneNode::itemChange(GraphicsItemChange change, const QVariant& value)
{
    if (change == ItemPositionHasChanged && scene()) {
        for(size_t i = edgeList.count(); i > 0; i--)
        {
            edgeList[i-1]->updatePos();
        }
    }
    return QGraphicsEllipseItem::itemChange(change, value);
}
