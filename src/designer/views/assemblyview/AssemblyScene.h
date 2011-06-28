#ifndef ASSEMBLYSCENE_H
#define ASSEMBLYSCENE_H

#include <QGraphicsScene>

#include <views/assemblyview/AssemblyLib.h>

class AssemblyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit AssemblyScene(QObject *parent = 0);

protected:
    //void dropEvent(QGraphicsSceneDragDropEvent *event);
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
signals:

public slots:

};

#endif // ASSEMBLYSCENE_H
