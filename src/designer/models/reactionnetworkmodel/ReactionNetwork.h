#ifndef REACTIONNETWORK_H
#define REACTIONNETWORK_H

#include <QObject>
#include <QScriptEngine>
#include "interfaces/DesignerModelItf.h"

class ReactionNetworkModel : public DesignerModelItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ReactionNetworkModel(DesignerDocItf *newDoc);

    DesignerModelFormatProxyItf* createImportProxy(QString importFormat);

    modelObjectIndex createModelObject(modelObjectIndex parent = 0, void* data = 0);
    void removeModelObject(modelObjectIndex index);
    void setModelObjectProperty(modelObjectIndex index, QString propertyName, QString value);
    QString getModelObjectProperty(modelObjectIndex index, QString propertyName);



signals:

public slots:

};

#endif // REACTIONNETWORK_H
