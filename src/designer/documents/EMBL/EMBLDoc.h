#ifndef EMBLDOC_H
#define EMBLDOC_H

#include "interfaces/DesignerDocItf.h"
#include "interfaces/DesignerModelItf.h"

class EMBLDoc : public DesignerDocItf
{

    Q_OBJECT
public:
    Q_INVOKABLE explicit EMBLDoc();
    ~EMBLDoc();

    virtual extentValue checkIfFileFitsDocumentType(QFile& file);
    virtual bool loadFromFile(QFile& file);
    virtual bool saveToFile(QFile& file);
};

#endif // EMBLDOC_H
