#ifndef ASSEMBLYITEMCOMPARTMENT_H
#define ASSEMBLYITEMCOMPARTMENT_H

#include <QString>
#include <QGraphicsEllipseItem>

#include <views/assemblyview/AssemblyLib.h>
#include <views/assemblyview/AssemblyItemPlasmid.h>

class AssemblyItemCompartment : public QGraphicsEllipseItem
{
public:
    explicit AssemblyItemCompartment( QString  setName , QGraphicsItem *parent = 0 );

signals:

public slots:

protected:
    //void mousePressEvent( QGraphicsSceneMouseEvent *event);
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    QString name;
    //bool pressed;
    //QPoint hotPoint;
};

#endif // ASSEMBLYITEMCOMPARTMENT_H
