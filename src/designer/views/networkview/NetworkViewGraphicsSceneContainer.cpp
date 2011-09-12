#include "NetworkViewGraphicsSceneContainer.h"
#include "NetworkViewContainerEditor.h"

NetworkViewGraphicsSceneContainer::NetworkViewGraphicsSceneContainer(QScriptValue value, QGraphicsItem *parent) :
    NetworkViewGraphicsItem( value , QObject::tr(":/designer/assemblyview/compartment_normal.png") , QObject::tr(":/designer/assemblyview/compartment_selected.png") , parent )
{
    Type = "container";    
    setResizable(true);
    setFlags( QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsSelectable | ItemSendsGeometryChanges);
}

bool NetworkViewGraphicsSceneContainer::addChild(QPointF scenePos, NetworkViewGraphicsItem *child)
{
    child->itemObject.setProperty("compartment",this->itemObject.property("id"));
    return NetworkViewGraphicsItem::addChild(scenePos,child);
}

void NetworkViewGraphicsSceneContainer::updatePos()
{
    foreach(NetworkViewGraphicsItem *child,children)
    {
        dynamic_cast<NetworkViewGraphicsSceneNode *>(child)->updatePos();
    }
    this->registPos();
}

QVariant NetworkViewGraphicsSceneContainer::itemChange(GraphicsItemChange change, const QVariant& value)
{
    if (change == ItemPositionHasChanged && scene()) {        
        updatePos();
    }
    return NetworkViewGraphicsItem::itemChange(change, value);
}

void NetworkViewGraphicsSceneContainer::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    NetworkViewContainerEditor dialog(itemObject,dynamic_cast<NetworkViewGraphicsScene *>(scene())->idSpace);
    dialog.exec();    
    NetworkViewGraphicsItem::mouseDoubleClickEvent(event);
}
