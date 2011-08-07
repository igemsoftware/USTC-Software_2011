#ifndef IGAME_H
#define IGAME_H

#include "interfaces/DesignerModelItf.h"

class IGameModel : public DesignerModelItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit IGameModel(DesignerDocItf *newDoc);

    virtual QStringList getSupportedViewList() const;
    virtual QStringList getSupportedDocumentList() const;

signals:

public slots:

};

#endif // IGAME_H
