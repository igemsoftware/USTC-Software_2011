#ifndef NETWORKVIEWGRAPHICSSCENELABEL_H
#define NETWORKVIEWGRAPHICSSCENELABEL_H

#include <QGraphicsTextItem>

class NetworkViewGraphicsSceneLabel : public QGraphicsTextItem
{
public:
    explicit NetworkViewGraphicsSceneLabel(QGraphicsItem* parent = 0, QString text = "");
};

#endif // NETWORKVIEWGRAPHICSSCENELABEL_H
