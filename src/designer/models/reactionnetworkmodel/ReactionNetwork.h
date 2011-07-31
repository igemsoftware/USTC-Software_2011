#ifndef REACTIONNETWORK_H
#define REACTIONNETWORK_H

#include "interfaces/DesignerModelItf.h"

class ReactionNetworkModel : public DesignerModelItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ReactionNetworkModel(DesignerDocItf *newDoc);

    virtual QStringList getSupportedViewList() const;
    virtual QStringList getSupportedDocumentList() const;

signals:

public slots:

};

#endif // REACTIONNETWORK_H
