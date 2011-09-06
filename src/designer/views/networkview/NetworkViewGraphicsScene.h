#ifndef NETWORKVIEWGRAPHICSSCENE_H
#define NETWORKVIEWGRAPHICSSCENE_H

#include <QtScript>
#include "DesignerDebug.h"
#include "interfaces/DesignerModelItf.h"

#include "NetworkViewGraphicsSceneEdge.h"
#include "QKeyEvent"
#include <QList>
#include <QtGui>
#include "interfaces/DesignerModelItf.h"
#include "NetworkViewGraphicsSceneContainer.h"

class DesignerModelItf;
class NetworkViewGraphicsItem;

class NetworkViewGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:

    QSet<QString> idSpace;
    DesignerModelItf * model;

    explicit NetworkViewGraphicsScene(QObject *parent = 0);
    void clearScene();
    void keyPressEvent(QKeyEvent *event);
    void loadFromModel(DesignerModelItf* model);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void addItem(QGraphicsItem *item);
    void removeItem(NetworkViewGraphicsItem *item);
    void refreshScriptValue();

signals:

public slots:

};

#endif // NETWORKVIEWGRAPHICSSCENE_H
