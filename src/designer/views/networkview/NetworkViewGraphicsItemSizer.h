#ifndef NETWORKVIEWGRAPHICSITEMSIZER_H
#define NETWORKVIEWGRAPHICSITEMSIZER_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class NetworkViewGraphicsItemSizer : public QGraphicsPixmapItem
{
public:
    explicit NetworkViewGraphicsItemSizer( QGraphicsItem * parent);

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // NETWORKVIEWGRAPHICSITEMSIZER_H
