#ifndef REACTIONNETWORKSBMLIMPORTPROXY_H
#define REACTIONNETWORKSBMLIMPORTPROXY_H

#include <QObject>
#include <QtScript>
#include <QtXml>
#include "ReactionNetwork.h"

class ReactionNetworkSBMLImportProxy : public DesignerModelFormatProxyItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ReactionNetworkSBMLImportProxy(ReactionNetworkModel *model = 0);
    ~ReactionNetworkSBMLImportProxy();

    QScriptEngine* getEngine();

private:
    QList<QScriptValue> itemPool;

public:
    virtual modelObjectIndex createModelObject(modelObjectIndex parent = 0, void* data = 0);
    virtual void setModelObjectProperty(modelObjectIndex index, QString propertyName, QString value);
    virtual QString getModelObjectProperty(modelObjectIndex index, QString propertyName);
    virtual void removeModelObject(modelObjectIndex index);


//signals:

//public slots:

};

#endif // REACTIONNETWORKSBMLIMPORTPROXY_H
