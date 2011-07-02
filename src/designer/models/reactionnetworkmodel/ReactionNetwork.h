#ifndef REACTIONNETWORK_H
#define REACTIONNETWORK_H

#include <QObject>
#include <QScriptEngine>
#include "DesignerModelItf.h"

class ReactionNetworkModel : public DesignerModelItf
{
    Q_OBJECT
public:
    explicit ReactionNetworkModel(QObject *parent = 0);

private:
    QScriptEngine modelEngine;

signals:

public slots:

};

#endif // REACTIONNETWORK_H
