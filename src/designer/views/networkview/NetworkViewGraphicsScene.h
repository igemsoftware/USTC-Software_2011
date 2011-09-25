#ifndef NETWORKVIEWGRAPHICSSCENE_H
#define NETWORKVIEWGRAPHICSSCENE_H

#include <QtScript>
#include "DesignerDebug.h"
#include "interfaces/DesignerModelItf.h"

#include "NetworkViewGraphicsSceneEdge.h"
#include "QKeyEvent"
#include <QList>
#include <QtGui>
#include "NetworkViewGraphicsSceneContainer.h"
#include "models/reactionnetworkmodel/ReactionNetwork.h"

class ReactionNetworkModel;
class NetworkViewGraphicsItem;
class NetworkViewGraphicsSceneNodeReaction;
class NetworkViewGraphicsSceneNodeSubstance;

class NetworkViewGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:

    bool loaded;
    bool locked;
    QSet<QString> *idSpace;
    QList<QGraphicsLineItem *> *lines;
    ReactionNetworkModel * model;
    NetworkViewGraphicsSceneNodeReaction *reaction;
    NetworkViewGraphicsSceneNodeSubstance *substance;
    explicit NetworkViewGraphicsScene(QObject *parent = 0);
    void clearScene();
    void keyPressEvent(QKeyEvent *event);
    void loadFromModel(DesignerModelComponent* model);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void addItem(QGraphicsItem *item);
    void removeItem(NetworkViewGraphicsItem *item);
    void removeLine(QGraphicsLineItem *line);
    void refreshScriptValue();
    void emitsignal();
    void wheelEvent(QGraphicsSceneWheelEvent *event);

signals:

public slots:

};

#endif // NETWORKVIEWGRAPHICSSCENE_H
