#ifndef REACTIONNETWORK_H
#define REACTIONNETWORK_H

#include "interfaces/DesignerModelItf.h"

class ReactionNetworkModel : public DesignerModelItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ReactionNetworkModel(DesignerDocItf *newDoc);

    DesignerModelFormatProxyItf* createImportProxy(QString importFormat);

    virtual QStringList getSupportedViewList() const;


signals:

public slots:

};

#endif // REACTIONNETWORK_H
