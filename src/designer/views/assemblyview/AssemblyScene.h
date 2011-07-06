#ifndef ASSEMBLYSCENE_H
#define ASSEMBLYSCENE_H

#include <QGraphicsScene>

#include "AssemblyLib.h"
#include "AssemblyItemBase.h"
#include "AssemblyItemPart.h"
#include "AssemblyItemCompartment.h"
#include "AssemblyItemPlasmid.h"


class AssemblyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit AssemblyScene(QObject *parent = 0);

    void removeItem( AssemblyItemBase *item);
    bool addItem( AssemblyItemBase * item );

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

    void wheelEvent(QGraphicsSceneWheelEvent *event);

    void keyPressEvent(QKeyEvent *event);

signals:
    void setScriptValue( QScriptValue value );
public slots:
    void propagateSelectionChange();
private:
    QMap<QString,AssemblyItemBase*> childrenMap;
};

#endif // ASSEMBLYSCENE_H
