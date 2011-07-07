#include "NetworkViewGraphicsSceneLabel.h"

NetworkViewGraphicsSceneLabel::NetworkViewGraphicsSceneLabel(QGraphicsItem* parent, QString text)
    : QGraphicsTextItem(parent)
{
    setPlainText(text);
}
