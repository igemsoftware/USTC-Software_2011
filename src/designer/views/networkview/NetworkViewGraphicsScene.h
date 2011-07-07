#ifndef NETWORKVIEWGRAPHICSSCENE_H
#define NETWORKVIEWGRAPHICSSCENE_H

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

    explicit NetworkViewGraphicsScene(QObject *parent = 0);

public:
    void clearScene();
    void loadFromModel(DesignerModelItf* model);

signals:

public slots:

};

#endif // NETWORKVIEWGRAPHICSSCENE_H
