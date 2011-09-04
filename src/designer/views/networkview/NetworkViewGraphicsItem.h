#ifndef NETWORKVIEWGRAPHICSITEM_H
#define NETWORKVIEWGRAPHICSITEM_H

#include <QtScript>

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QPixmap>
#include <QGraphicsScene>
#include "NetworkViewGraphicsItemSizer.h"

class NetworkViewGraphicsItem : public QGraphicsPixmapItem
{
public:
    explicit NetworkViewGraphicsItem( QScriptValue & newScriptValue , QString normalImagePath , QString selectedImagePath , QGraphicsItem * parent = 0 );
    virtual ~NetworkViewGraphicsItem();
    QString getId();
    void setId( QString newId );
    QString getName();
    void setName( QString newName );
    QScriptValue itemObject;
    QScriptValue getScriptValue();
    virtual void setScriptValue( QScriptValue & newScriptValue );
    QList<NetworkViewGraphicsItem *> children ;

    virtual bool addChild( QPointF scenePos , NetworkViewGraphicsItem * child );
    virtual void removeChild( NetworkViewGraphicsItem * child );
    virtual void refreshScriptValue();

    virtual void getSelection();
    virtual void loseSelection( QList<QGraphicsItem*> newSelectedItems );
    void resize( qreal newWidth , qreal newHeight );
    void setResizable( bool newResizable );
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void detectEdge();

protected:
    bool resizable;
    QString Type;
    QGraphicsTextItem * displayName;
    NetworkViewGraphicsItemSizer * sizer;

    void setImage( QPixmap newNormalImage , QPixmap newSelectedImage);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    QPixmap normalImage , originalNormalImage;
    QPixmap selectedImage , originalSelectedImage;    
    bool moving;
    bool selected;
};

#endif // NETWORKVIEWGRAPHICSITEM_H
