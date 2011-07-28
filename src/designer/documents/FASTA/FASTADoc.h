#ifndef FASTADOC_H
#define FASTADOC_H

#include "interfaces/DesignerDocItf.h"
#include "interfaces/DesignerModelItf.h"

class FASTADoc : public DesignerDocItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit FASTADoc();
    ~FASTADoc();

    virtual extentValue checkIfFileFitsDocumentType(QFile& file);
    virtual bool loadFromFile(QFile& file);
    virtual bool saveToFile(QFile& file);

};

#endif // FASTADOC_H
