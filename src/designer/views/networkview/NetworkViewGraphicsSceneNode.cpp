#include "NetworkViewGraphicsSceneContainer.h"
#include "NetworkViewGraphicsSceneNode.h"
#include "NetworkViewGraphicsSceneEdge.h"
#include "NetworkViewGraphicsSceneLabel.h"
#include <QMessageBox>

NetworkViewGraphicsSceneNode::NetworkViewGraphicsSceneNode(QGraphicsItem *parent, QScriptValue value ,QString normalImagePath , QString selectedImagePath , bool isParentContainer)
    : NetworkViewGraphicsItem( value , normalImagePath , selectedImagePath , parent )
{
    setFlags( QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsSelectable | ItemSendsGeometryChanges);
    labelObject = new NetworkViewGraphicsSceneLabel(this);
    if(dynamic_cast<NetworkViewGraphicsItem*>(parent))dynamic_cast<NetworkViewGraphicsItem*>(parent)->addChild(scenePos(),this);
    setZValue(1);
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
//        QList<QGraphicsItem *> colliding=scene()->collidingItems(this);
//        bool haspartent=false;
//        if(this->parentItem()&&dynamic_cast<NetworkViewGraphicsItem *>(this->parentItem()))
//            dynamic_cast<NetworkViewGraphicsItem *>(this->parentItem())->removeChild(this);
//        foreach(QGraphicsItem * item,colliding)
//        {
//            if(dynamic_cast<NetworkViewGraphicsSceneContainer *>(item))
//            {
//                QList<NetworkViewGraphicsItem *> children=dynamic_cast<NetworkViewGraphicsSceneContainer *>(item)->children;
//                QMessageBox *qmb=new QMessageBox();
//                qmb->setText(QString::number(children.count()));
//                qmb->exec();

//                if(children.indexOf(this)==-1)
//                    dynamic_cast<NetworkViewGraphicsSceneContainer *>(item)->addChild(scenePos(),this);

//                haspartent=true;
//                break;
//            }
//        }
//        if(!haspartent)
//            setParentItem(0);
        //this->setParentItem(0);
        updatePos();
    }
    return NetworkViewGraphicsItem::itemChange(change, value);
}

void NetworkViewGraphicsSceneNode::setLabel(QString label)
{
    labelObject->setPlainText(label);
}

void NetworkViewGraphicsSceneNode::deleteEdges()
{
    while(this->edgeList.count()!=0)
    {
        delete edgeList[0];
    }
    this->edgeList.clear();
}

void NetworkViewGraphicsSceneNode::deleteEdge(NetworkViewGraphicsSceneEdge *edge)
{
    for(int i=0;i<this->edgeList.count();i++)
    {
        if(edge==edgeList[i])
           this->edgeList.removeAt(i);
    }
}
