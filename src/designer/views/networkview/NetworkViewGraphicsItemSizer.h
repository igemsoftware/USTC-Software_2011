#ifndef NETWORKVIEWGRAPHICSITEMSIZER_H
#define NETWORKVIEWGRAPHICSITEMSIZER_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class NetworkViewGraphicsItemSizer : public QGraphicsPixmapItem
{
public:
    explicit NetworkViewGraphicsItemSizer( QGraphicsItem * parent);
//    virtual void getSelection();
//    virtual void loseSelection( QList<QGraphicsItem*> newSelectedItems );
protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // NETWORKVIEWGRAPHICSITEMSIZER_H
