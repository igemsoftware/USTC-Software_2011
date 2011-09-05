#ifndef NETWORKVIEWGRAPHICSSCENE_H
#define NETWORKVIEWGRAPHICSSCENE_H

#include <QtScript>
#include <QGraphicsScene>
#include <QGraphicsItem>

class DesignerModelItf;

class NetworkViewGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum
    {
        NetworkViewGraphicsItemStartIndex = QGraphicsItem::UserType + 100
    };
    QSet<QString> idSpace;
    explicit NetworkViewGraphicsScene(QObject *parent = 0);
    void clearScene();
    void keyPressEvent(QKeyEvent *event);
    void loadFromModel(DesignerModelItf* model);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void addItem(QGraphicsItem *item);

signals:

public slots:

};

#endif // NETWORKVIEWGRAPHICSSCENE_H
