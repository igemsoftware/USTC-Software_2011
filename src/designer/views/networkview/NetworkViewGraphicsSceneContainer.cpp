#include "NetworkViewGraphicsSceneContainer.h"
#include "NetworkViewGraphicsSceneLabel.h"
#include <QMessageBox>

NetworkViewGraphicsSceneContainer::NetworkViewGraphicsSceneContainer(QGraphicsItem *parent, QScriptValue value) :
    NetworkViewGraphicsItem( value , QObject::tr(":/designer/assemblyview/compartment_normal.png") , QObject::tr(":/designer/assemblyview/compartment_selected.png") , parent )
{
    Type = "container";
    setFlags( QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsSelectable | ItemSendsGeometryChanges);
//    labelObject = new NetworkViewGraphicsSceneLabel(this);
//    labelObject->setPos(0, radius);
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
        QMessageBox *qmb=new QMessageBox();
        qmb->setText(QString::number(children.count()));
        qmb->exec();
        if(dynamic_cast<NetworkViewGraphicsSceneNode *>(this->children[0]))
            dynamic_cast<NetworkViewGraphicsSceneNode *>(this->children[0])->deleteEdges();
        delete this->children[0];
    }
    this->children.clear();
}

//void NetworkViewGraphicsSceneContainer::deleteNode(NetworkViewGraphicsSceneNode *node)
//{
//    for(int i=0;i<this->nodeList.count();i++)
//    {
//        if(node==nodeList[i])
//            nodeList.removeAt(i);
//    }
//}
