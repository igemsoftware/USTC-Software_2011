#ifndef REACTIONNETWORK_H
#define REACTIONNETWORK_H

#include <QObject>
#include <QScriptEngine>
#include "DesignerModelItf.h"

class ReactionNetworkModel : public DesignerModelItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ReactionNetworkModel(QObject *parent = 0);

    DesignerModelFormatProxyItf* createImportProxy(QString importFormat);

    modelObjectIndex createModelObject(modelObjectIndex parent = 0, void* data = 0);
    void removeModelObject(modelObjectIndex index);
    void setModelObjectProperty(modelObjectIndex index, QString propertyName, QString value);
    QString getModelObjectProperty(modelObjectIndex index, QString propertyName);

private:
    QScriptEngine modelEngine;
public:
    QScriptEngine* getEngine() {return &modelEngine;}

signals:

public slots:

};

#endif // REACTIONNETWORK_H
