#ifndef SYNTHETICBIOLOGICALPART_H
#define SYNTHETICBIOLOGICALPART_H

#include "interfaces/DesignerModelItf.h"

class SyntheticBiologicalPartModel : public DesignerModelComponent
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SyntheticBiologicalPartModel(DesignerDocComponent *newDoc);

    virtual QStringList getSupportedViewList() const;
    virtual QStringList getSupportedDocumentList() const;

signals:


public slots:

};

#endif // SYNTHETICBIOLOGICALPART_H
