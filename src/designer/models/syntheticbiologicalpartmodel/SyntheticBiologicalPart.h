#ifndef SYNTHETICBIOLOGICALPART_H
#define SYNTHETICBIOLOGICALPART_H

#include "interfaces/DesignerModelItf.h"

class SyntheticBiologicalPartModel : public DesignerModelItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SyntheticBiologicalPartModel(DesignerDocItf *newDoc);

    virtual QStringList getSupportedViewList() const;

signals:


public slots:

};

#endif // SYNTHETICBIOLOGICALPART_H
