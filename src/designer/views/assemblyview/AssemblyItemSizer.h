#ifndef ASSEMBLYITEMSIZER_H
#define ASSEMBLYITEMSIZER_H

#include <QGraphicsRectItem>

class AssemblyItemCompartment;

class AssemblyItemSizer : public QGraphicsRectItem
{
public:
    explicit AssemblyItemSizer( qreal px , qreal py , QGraphicsItem *parent = 0);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    AssemblyItemCompartment * father;
};

#endif // ASSEMBLYITEMSIZER_H
