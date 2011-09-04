#include "NetworkViewGraphicsSceneContainer.h"
#include "NetworkViewGraphicsSceneLabel.h"
#include <QtGui>

NetworkViewGraphicsSceneContainer::NetworkViewGraphicsSceneContainer(QScriptValue value, QGraphicsItem *parent) :
    NetworkViewGraphicsItem( value , QObject::tr(":/designer/assemblyview/compartment_normal.png") , QObject::tr(":/designer/assemblyview/compartment_selected.png") , parent )
{
    Type = "container";    
    setResizable(true);
    setFlags( QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsSelectable | ItemSendsGeometryChanges);
}


//void NetworkViewGraphicsSceneContainer::registerNode(NetworkViewGraphicsSceneNode* node)
//{
//    if(node && nodeList.indexOf(node)==-1) nodeList.append(node);
//}

void NetworkViewGraphicsSceneContainer::updatePos()
{

    foreach(NetworkViewGraphicsItem *child,children)
    {
        dynamic_cast<NetworkViewGraphicsSceneNode *>(child)->updatePos();
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
    while(children.count()!=0)
    {
        if(dynamic_cast<NetworkViewGraphicsSceneNode *>(this->children[0]))
            dynamic_cast<NetworkViewGraphicsSceneNode *>(this->children[0])->deleteEdges();
        delete this->children[0];
    }
    this->children.clear();
}
