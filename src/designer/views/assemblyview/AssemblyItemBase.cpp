#include "AssemblyItemBase.h"
#include "AssemblyScene.h"
#include <QGraphicsSceneMouseEvent>

AssemblyItemBase::AssemblyItemBase( QString newName , QString normalImagePath , QString selectedImagePath , QGraphicsItem * parent ) :
    QGraphicsPixmapItem( parent )
{
    resizable = false;
    moving = false;
    sizer = 0;
    name = newName;
    normalImage.load( normalImagePath );
    originalNormalImage.load(normalImagePath);
    selectedImage.load( selectedImagePath );
    originalSelectedImage.load( selectedImagePath );
    setPixmap( normalImage );

    setFlag( QGraphicsItem::ItemIsSelectable );
    setFlag( QGraphicsItem::ItemIsMovable );

    displayName = new QGraphicsTextItem( name , this );
    displayName->adjustSize();
    QRectF bound = mapRectToScene(boundingRect());
    foreach( AssemblyItemBase* child , getChildren() ) bound |= mapRectToScene(child->boundingRect());
    displayName->setPos( ( bound.width() - displayName->textWidth() )/2 , bound.height() );
}

AssemblyItemBase::~AssemblyItemBase()
{
    if( resizable ) delete sizer;
    delete displayName;
    if( dynamic_cast<AssemblyItemBase*>(parentItem()) ) dynamic_cast<AssemblyItemBase*>(parentItem())->removeChild(this);
    if( scene() ) dynamic_cast<AssemblyScene*>(scene())->removeItem(this);
}

QString AssemblyItemBase::getName(){ return name; }
void AssemblyItemBase::setName(QString newName){ name = newName; }

QList<AssemblyItemBase*> AssemblyItemBase::getChildren(){ QList<AssemblyItemBase*> nothing; return nothing; }

bool AssemblyItemBase::addChild( QPointF scenePos , AssemblyItemBase * child )
{
    child->setParentItem(this);
    child->setPos( mapFromScene(scenePos) );
    return true;
}

void AssemblyItemBase::removeChild( AssemblyItemBase *child )
{
    child->setParentItem(0);
}

void AssemblyItemBase::getSelection()
{
    selected = true;
    setPixmap(selectedImage);
    if( resizable ) sizer->show();
}

void AssemblyItemBase::loseSelection( QList<QGraphicsItem*> newSelectedItems )
{
    selected = false;
    setPixmap(normalImage);
    //if( resizable && !newSelectedItems.contains(sizer) ) sizer->hide();
}

void AssemblyItemBase::resize( qreal newWidth , qreal newHeight )
{
    normalImage = originalNormalImage.scaled( newWidth , newHeight , Qt::IgnoreAspectRatio , Qt::SmoothTransformation );
    selectedImage = originalSelectedImage.scaled( newWidth , newHeight , Qt::IgnoreAspectRatio , Qt::SmoothTransformation );
    if( selected )
        setPixmap(selectedImage);
    else
        setPixmap(normalImage);

    /*qreal sx = newWidth/boundingRect().width();
    qreal sy = newHeight/boundingRect().height();
    scale(1,1);
    scale( sx , sy );*/
    if( resizable ) sizer->setPos( boundingRect().width() - sizer->pixmap().width()/2 , boundingRect().height() - sizer->pixmap().height()/2 );
    QRectF bound = mapRectToScene(boundingRect());
    foreach( AssemblyItemBase* child , getChildren() ) bound |= mapRectToScene(child->boundingRect());
    displayName->setPos( ( bound.width() - displayName->textWidth() )/2 , bound.height() );
}

void AssemblyItemBase::setImage(QPixmap newNormalImage, QPixmap newSelectedImage)
{
    normalImage = newNormalImage;
    selectedImage = newSelectedImage;
}

void AssemblyItemBase::setResizable(bool newResizable)
{
    if( newResizable != resizable )
    {
        if( newResizable )
        {
            sizer = new AssemblyItemSizer(this);
        }else
        {
            delete sizer;
        }
        resizable = newResizable;
    }
}

void AssemblyItemBase::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if( !moving )
    {
        moving = true;
        QPointF tempPos = scenePos();
        if( dynamic_cast<AssemblyItemBase*>(parentItem()) ) dynamic_cast<AssemblyItemBase*>(parentItem())->removeChild(this);
        setPos(tempPos);
    }
    QGraphicsPixmapItem::mouseMoveEvent(event);
}


void AssemblyItemBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPixmapItem::mouseReleaseEvent(event);
    if( moving )
    {
        moving = false;
        dynamic_cast<AssemblyScene*>(scene())->addItem(this);
    }
}


AssemblyItemSizer::AssemblyItemSizer(QGraphicsItem *parent) :
    AssemblyItemBase( QObject::tr("") , QObject::tr(":/designer/assemblyview/sizer_normal.png") , QObject::tr(":/designer/assemblyview/sizer_selected.png") , parent )
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    hide();
    setPos( dynamic_cast<AssemblyItemBase*>( parentItem() )->pixmap().width() - pixmap().width()/2 , dynamic_cast<AssemblyItemBase*>( parentItem() )->pixmap().height() - pixmap().height()/2 );
}

void AssemblyItemSizer::mousePressEvent(QGraphicsSceneMouseEvent *event)
{    
    QGraphicsItem::mousePressEvent(event);
    AssemblyItemBase::getSelection();
}

void AssemblyItemSizer::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    QList<QGraphicsItem*> nothing;
    AssemblyItemBase::loseSelection(nothing);
}

void AssemblyItemSizer::getSelection(){}
void AssemblyItemSizer::loseSelection(QList<QGraphicsItem *> newSelectedItems){  }

void AssemblyItemSizer::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPixmapItem::mouseMoveEvent(event);
    QPointF point = mapToParent(mapFromScene( scenePos() + QPointF( pixmap().width()/2 , pixmap().height()/2 ) ) );
    dynamic_cast<AssemblyItemBase*>(parentItem())->resize( point.x() , point.y() );
}



















