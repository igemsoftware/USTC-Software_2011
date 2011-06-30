#ifndef PROTEININTERACTIONNETWORKMODEL_H
#define PROTEININTERACTIONNETWORKMODEL_H

#include <QObject>
#include <QScriptEngine>
#include "DesignerModelItf.h"

class ProteinInteractionNetworkModel : public DesignerModelItf
{
    Q_OBJECT
public:
    explicit ProteinInteractionNetworkModel(QObject *parent = 0);

private:
    QScriptEngine modelEngine;

signals:

public slots:

};

#endif // PROTEININTERACTIONNETWORKMODEL_H
