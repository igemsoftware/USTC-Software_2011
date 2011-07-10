#include "NetworkViewGraphicsSceneContainer.h"
#include "NetworkViewGraphicsSceneLabel.h"

NetworkViewGraphicsSceneContainer::NetworkViewGraphicsSceneContainer(QGraphicsItem *parent) :
    QGraphicsEllipseItem(-radius, -radius, radius*2, radius*2, parent)
{
    setFlags( QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsSelectable | ItemSendsGeometryChanges);
    labelObject = new NetworkViewGraphicsSceneLabel(this);
}


void NetworkViewGraphicsSceneContainer::registerNode(NetworkViewGraphicsSceneNode* node)
{
    if(node && nodeList.indexOf(node)==-1) nodeList.append(node);
}

void NetworkViewGraphicsSceneContainer::updatePos()
{
    for(size_t i = nodeList.count(); i > 0; i--)
    {
        nodeList[i-1]->updatePos();
    }
}

QVariant NetworkViewGraphicsSceneContainer::itemChange(GraphicsItemChange change, const QVariant& value)
{
    if (change == ItemPositionHasChanged && scene()) {
        updatePos();
    }
    return QGraphicsEllipseItem::itemChange(change, value);
}
