#ifndef NETWORKVIEWGRAPHICSITEM_H
#define NETWORKVIEWGRAPHICSITEM_H

#include <QtScript>
#include <QtGui>
#include "NetworkViewGraphicsItemSizer.h"

class NetworkViewGraphicsItem : public QGraphicsPixmapItem
{
public:
    explicit NetworkViewGraphicsItem( QScriptValue & newScriptValue , QString normalImagePath , QString selectedImagePath , QGraphicsItem * parent = 0 );
    virtual ~NetworkViewGraphicsItem();
    QString getId();
    QString Type;
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
    virtual void registPos();
    virtual void setPositon();

    void resize( qreal newWidth , qreal newHeight );
    void setResizable( bool newResizable );
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    bool detectEdge();

protected:
    bool resizable;    
    QGraphicsTextItem * displayName;
    NetworkViewGraphicsItemSizer * sizer;

    void setImage( QPixmap newNormalImage , QPixmap newSelectedImage);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);    

private:
    QPixmap normalImage , originalNormalImage;
    QPixmap selectedImage , originalSelectedImage;    
    bool moving;
    bool selected;
};

#endif // NETWORKVIEWGRAPHICSITEM_H
