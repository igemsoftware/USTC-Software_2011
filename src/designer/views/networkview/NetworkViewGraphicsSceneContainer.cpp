#include "NetworkViewGraphicsSceneContainer.h"
#include "NetworkViewGraphicsSceneLabel.h"

NetworkViewGraphicsSceneContainer::NetworkViewGraphicsSceneContainer(QGraphicsItem *parent, QScriptValue value) :
    NetworkViewGraphicsItem( value , QObject::tr(":/designer/assemblyview/compartment_normal.png") , QObject::tr(":/designer/assemblyview/compartment_selected.png") , parent )
{
    Type = "container";
    setFlags( QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsSelectable | ItemSendsGeometryChanges);
    labelObject = new NetworkViewGraphicsSceneLabel(this);
    labelObject->setPos(0, radius);
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
    return NetworkViewGraphicsItem::itemChange(change, value);
}

void NetworkViewGraphicsSceneContainer::setLabel(QString label)
{
    labelObject->setPlainText(label);
}

void NetworkViewGraphicsSceneContainer::deleteNodes()
{
    for(int i=0;i<this->nodeList.count();i++)
    {
        this->nodeList[i]->deleteEdge();
        delete this->nodeList[i];
    }
}
