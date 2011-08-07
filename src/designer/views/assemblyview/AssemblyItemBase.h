#ifndef ASSEMBLYITEMBASE_H
#define ASSEMBLYITEMBASE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QPixmap>
#include <QGraphicsScene>
#include "AssemblyLib.h"

class AssemblyItemSizer;

class AssemblyItemBase : public QGraphicsPixmapItem
{
public:
    explicit AssemblyItemBase( QScriptValue & newScriptValue , QString normalImagePath , QString selectedImagePath , QGraphicsItem * parent = 0 );
    virtual ~AssemblyItemBase();

    QString getId();
    void setId( QString newId );
    QString getName();
    void setName( QString newName );
    QScriptValue getScriptValue();
    void setScriptValue( QScriptValue & newScriptValue );

    virtual QList<AssemblyItemBase*> getChildren();
    virtual bool addChild( QPointF scenePos , AssemblyItemBase * child );
    virtual void removeChild( AssemblyItemBase * child );
    virtual void refreshScriptValue();

    virtual void getSelection();
    virtual void loseSelection( QList<QGraphicsItem*> newSelectedItems );
    virtual void resize( qreal newWidth , qreal newHeight );


protected:
    QScriptValue scriptValue;
    bool resizable;
    QGraphicsTextItem * displayName;

    void setResizable( bool newResizable );
    void setImage( QPixmap newNormalImage , QPixmap newSelectedImage );

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private:
    QPixmap normalImage , originalNormalImage;
    QPixmap selectedImage , originalSelectedImage;
    AssemblyItemSizer * sizer;
    bool moving;
    bool selected;

};

class AssemblyItemSizer : public AssemblyItemBase
{
public:
    explicit AssemblyItemSizer( QGraphicsItem * parent = 0 );
    virtual void getSelection();
    virtual void loseSelection( QList<QGraphicsItem*> newSelectedItems );
protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // ASSEMBLYITEMBASE_H
