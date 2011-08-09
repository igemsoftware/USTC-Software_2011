#include "AssemblyItemBase.h"
#include "AssemblyScene.h"
#include <QGraphicsSceneMouseEvent>

AssemblyItemBase::AssemblyItemBase( QScriptValue & newScriptValue , QString normalImagePath , QString selectedImagePath , QGraphicsItem * parent ) :
    QGraphicsPixmapItem( parent )
{
    resizable = false;
    moving = false;
    sizer = 0;
    scriptValue = newScriptValue;
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

AssemblyItemBase::~AssemblyItemBase()
{
    if( resizable ) delete sizer;
    delete displayName;
    if( dynamic_cast<AssemblyItemBase*>(parentItem()) ) dynamic_cast<AssemblyItemBase*>(parentItem())->removeChild(this);
    if( scene() ) dynamic_cast<AssemblyScene*>(scene())->removeItem(this);
}

QString AssemblyItemBase::getId(){ return scriptValue.property("id").toString(); }
void AssemblyItemBase::setId(QString newId){ scriptValue.setProperty("id",QScriptValue(newId) ); }

QString AssemblyItemBase::getName(){ return scriptValue.property("name").toString(); }
void AssemblyItemBase::setName(QString newName){ scriptValue.setProperty("name",QScriptValue(newName) ); }

QScriptValue AssemblyItemBase::getScriptValue(){ return scriptValue; }
void AssemblyItemBase::setScriptValue( QScriptValue & newScriptValue )
{
    scriptValue = newScriptValue;
    displayName->setPlainText( scriptValue.property("id").toString() );
    displayName->adjustSize();
    QRectF bound = mapRectToScene(boundingRect());
    foreach( AssemblyItemBase* child , getChildren() ) bound |= mapRectToScene(child->childrenBoundingRect());
    displayName->setPos( ( bound.width() - displayName->textWidth() )/2 , bound.height() );
}

QList<AssemblyItemBase*> AssemblyItemBase::getChildren(){ QList<AssemblyItemBase*> nothing; return nothing; }

bool AssemblyItemBase::addChild( QPointF scenePos , AssemblyItemBase * child )
{
    if( child->isAncestorOf(this) ) return false;
    child->setParentItem(this);
    child->setPos( mapFromScene(scenePos) );
    return true;
}

void AssemblyItemBase::removeChild( AssemblyItemBase *child )
{
    child->setParentItem(0);
}

void AssemblyItemBase::refreshScriptValue()
{
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
        dynamic_cast<AssemblyScene*>(scene())->addItem(this,false);
    }
}


void AssemblyItemBase::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QScriptValueList tmp;
    tmp.push_back( copyFromScriptValue( getScriptValue().engine() , getScriptValue() ) );
    AssemblyPropertyEditor dialog(type,tmp);
    if( dialog.exec() == QDialog::Accepted )
    {
        if( dynamic_cast<AssemblyScene*>(scene())->reassignId( scriptValue.property("id").toString() , tmp[0].property("id").toString() ) )
            setScriptValue( tmp[0] );
        else
            QMessageBox::information(0,"Error","Edit denied due to incompatible id specified!");
    }
}

AssemblyItemSizer::AssemblyItemSizer(QGraphicsItem *parent) :
    AssemblyItemBase( scriptValue , QObject::tr(":/designer/assemblyview/sizer_normal.png") , QObject::tr(":/designer/assemblyview/sizer_selected.png") , parent )
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


















