#include "NetworkViewGraphicsItem.h"
#include "NetworkViewGraphicsScene.h"
#include "NetworkViewGraphicsSceneContainer.h"
#include <QtGui>

NetworkViewGraphicsItem::NetworkViewGraphicsItem( QScriptValue & newScriptValue , QString normalImagePath , QString selectedImagePath , QGraphicsItem * parent ) :
    QGraphicsPixmapItem( parent )
{
    resizable = false;
    moving = false;
    sizer = 0;
    itemObject = newScriptValue;
    qDebug() << normalImagePath;
    normalImage.load( normalImagePath );
    originalNormalImage.load(normalImagePath);
    selectedImage.load( selectedImagePath );
    originalSelectedImage.load( selectedImagePath );
    setPixmap( normalImage );

    setFlag( QGraphicsItem::ItemIsSelectable );
    setFlag( QGraphicsItem::ItemIsMovable );

    displayName = new QGraphicsTextItem( getId() , this );    
    setScriptValue( newScriptValue );    
}

NetworkViewGraphicsItem::~NetworkViewGraphicsItem()
{
    if( resizable ) delete sizer;
    delete displayName;
    if( dynamic_cast<NetworkViewGraphicsItem*>(parentItem()) ) dynamic_cast<NetworkViewGraphicsItem*>(parentItem())->removeChild(this);
    if( scene() ) dynamic_cast<NetworkViewGraphicsScene*>(scene())->removeItem(this);
}

QString NetworkViewGraphicsItem::getId(){ return itemObject.property("id").toString(); }
void NetworkViewGraphicsItem::setId(QString newId){ itemObject.setProperty("id",QScriptValue(newId) ); }

QString NetworkViewGraphicsItem::getName(){ return itemObject.property("name").toString(); }
void NetworkViewGraphicsItem::setName(QString newName){ itemObject.setProperty("name",QScriptValue(newName) ); }

QScriptValue NetworkViewGraphicsItem::getScriptValue(){ return itemObject; }
void NetworkViewGraphicsItem::setScriptValue( QScriptValue & newScriptValue )
{
    itemObject = newScriptValue;
    displayName->setPlainText( itemObject.property("id").toString() );
    displayName->adjustSize();
    QRectF bound = mapRectToScene(boundingRect());
    foreach( NetworkViewGraphicsItem* child , children ) bound |= mapRectToScene(child->childrenBoundingRect());
    displayName->setPos( ( bound.width() - displayName->textWidth() )/2 , bound.height() );
}

bool NetworkViewGraphicsItem::addChild( QPointF scenePos , NetworkViewGraphicsItem * child )
{
    if( child->isAncestorOf(this) ) return false;
    child->setParentItem(this);
    child->setPos( mapFromScene(scenePos) );
    children.append(child);
    return true;
}

void NetworkViewGraphicsItem::removeChild( NetworkViewGraphicsItem *child )
{
    //child->setParentItem(0);
    for(int i=0;i<children.count();i++)
    {
        if(children[i]==child)
            children.removeAt(i);
    }
}

void NetworkViewGraphicsItem::refreshScriptValue()
{
}

void NetworkViewGraphicsItem::getSelection()
{
    selected = true;
    setPixmap(selectedImage);
    if( resizable )
    {
        sizer->show();
    }
}

void NetworkViewGraphicsItem::loseSelection( QList<QGraphicsItem*> newSelectedItems )
{
    selected = false;
    setPixmap(normalImage);
    if( resizable && !newSelectedItems.contains(sizer) ) sizer->hide();
}

void NetworkViewGraphicsItem::resize( qreal newWidth , qreal newHeight )
{
    if( newWidth < originalNormalImage.width()*0.1 || newHeight < originalNormalImage.width()*0.1 )
    {
        if( scene() ) scene()->clearSelection();
        if( resizable ) sizer->setPos( boundingRect().width() - sizer->pixmap().width()/2 , boundingRect().height() - sizer->pixmap().height()/2 );
        return;
    }
    normalImage = originalNormalImage.scaled( newWidth , newHeight , Qt::IgnoreAspectRatio , Qt::SmoothTransformation );
    selectedImage = originalSelectedImage.scaled( newWidth , newHeight , Qt::IgnoreAspectRatio , Qt::SmoothTransformation );
    if( selected )
        setPixmap(selectedImage);
    else
        setPixmap(normalImage);
    if( resizable ) sizer->setPos( boundingRect().width() - sizer->pixmap().width()/2 , boundingRect().height() - sizer->pixmap().height()/2 );
    QRectF bound = mapRectToScene(boundingRect());
    foreach( NetworkViewGraphicsItem* child , children ) bound |= mapRectToScene(child->boundingRect());
    displayName->setPos( ( bound.width() - displayName->textWidth() )/2 , bound.height() );
}

void NetworkViewGraphicsItem::setImage(QPixmap newNormalImage, QPixmap newSelectedImage)
{
    normalImage = newNormalImage;
    selectedImage = newSelectedImage;
}


void NetworkViewGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if( !moving )
    {
        moving = true;
//        if( dynamic_cast<NetworkViewGraphicsSceneContainer*>(parentItem()))
//            dynamic_cast<NetworkViewGraphicsSceneContainer*>(parentItem())->removeChild(this);
//        QPointF tempPos = scenePos();
//        setPos(tempPos);
    }
    QGraphicsPixmapItem::mouseMoveEvent(event);
}


void NetworkViewGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPixmapItem::mouseReleaseEvent(event);
    if(dynamic_cast<NetworkViewGraphicsSceneNode *>(this))
        detectEdge();
}

void NetworkViewGraphicsItem::setResizable(bool newResizable)
{
    if( newResizable != resizable )
    {
        if( newResizable )
        {
            sizer = new NetworkViewGraphicsItemSizer(this);
        }else
        {
            delete sizer;
        }
        resizable = newResizable;
    }
}

void NetworkViewGraphicsItem::detectEdge()
{
    QList<QGraphicsItem *> colliding;
    colliding=scene()->collidingItems(this);
    foreach(QGraphicsItem * item,colliding)
    {
        if(dynamic_cast<NetworkViewGraphicsSceneContainer *>(item))
        {
        QList<NetworkViewGraphicsItem *> children=dynamic_cast<NetworkViewGraphicsSceneContainer *>(item)->children;
        if(children.indexOf(this)==-1)
        dynamic_cast<NetworkViewGraphicsSceneContainer *>(item)->addChild(scenePos(),this);
        return;
        }
    }

    if( dynamic_cast<NetworkViewGraphicsSceneContainer*>(parentItem()))
    {
        dynamic_cast<NetworkViewGraphicsSceneContainer*>(parentItem())->removeChild(this);
        QPointF tempPos=scenePos();
        setParentItem(0);
        setPos(tempPos);
    }
}

//void NetworkViewGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
//{
//    QScriptValueList tmp;
//    tmp.push_back( copyFromScriptValue( getScriptValue().engine() , getScriptValue() ) );
//    AssemblyPropertyEditor dialog(type,tmp,scriptValue.engine());
//    if( dialog.exec() == QDialog::Accepted )
//    {
//        if( dynamic_cast<AssemblyScene*>(scene())->reassignId( scriptValue.property("id").toString() , tmp[0].property("id").toString() ) )
//            setScriptValue( tmp[0] );
//        else
//            QMessageBox::information(0,"Error","Edit denied due to incompatible id specified!");
//    }
//}
