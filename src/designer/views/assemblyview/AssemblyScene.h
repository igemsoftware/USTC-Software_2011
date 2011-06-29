#ifndef ASSEMBLYSCENE_H
#define ASSEMBLYSCENE_H

#include <QGraphicsScene>

#include <views/assemblyview/AssemblyLib.h>
#include <views/assemblyview/AssemblyItemBrick.h>
#include <views/assemblyview/AssemblyItemCompartment.h>
#include <views/assemblyview/AssemblyItemPlasmid.h>

class AssemblyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit AssemblyScene(QObject *parent = 0);

    void removeItem(QGraphicsItem *item);

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

    void wheelEvent(QGraphicsSceneWheelEvent *event);

    void keyPressEvent(QKeyEvent *event);

signals:

public slots:
    void selectionMessage();

private:
    QMap<QString,AssemblyItemCompartment*> compartmentMap;
    QMap<QString,AssemblyItemPlasmid*> plasmidMap;
    QList<QGraphicsItem*> previousSelection;
};

#endif // ASSEMBLYSCENE_H
