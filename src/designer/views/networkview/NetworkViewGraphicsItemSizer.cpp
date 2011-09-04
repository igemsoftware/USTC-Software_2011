#include "NetworkViewGraphicsItemSizer.h"
#include "NetworkViewGraphicsItem.h"
#include <QtGui>

NetworkViewGraphicsItemSizer::NetworkViewGraphicsItemSizer(QGraphicsItem *parent):
    QGraphicsPixmapItem( parent )
{
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    this->setPixmap(*(new QPixmap(":/designer/assemblyview/sizer_normal.png")));
    setPos( dynamic_cast<NetworkViewGraphicsItem*>( parentItem() )->pixmap().width() - pixmap().width()/2 , dynamic_cast<NetworkViewGraphicsItem*>( parentItem() )->pixmap().height() - pixmap().height()/2 );
    hide();
}

void NetworkViewGraphicsItemSizer::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    this->setSelected(true);
    //NetworkViewGraphicsItem::getSelection();
}

void NetworkViewGraphicsItemSizer::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    this->setSelected(false);
    //dynamic_cast<NetworkViewGraphicsItem*>(parentItem())->loseSelection(scene()->selectedItems());
}

void NetworkViewGraphicsItemSizer::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPixmapItem::mouseMoveEvent(event);
    QPointF point = mapToParent(mapFromScene( scenePos() + QPointF( pixmap().width()/2 , pixmap().height()/2 ) ) );
    dynamic_cast<NetworkViewGraphicsItem*>(parentItem())->resize( point.x() , point.y() );
}

