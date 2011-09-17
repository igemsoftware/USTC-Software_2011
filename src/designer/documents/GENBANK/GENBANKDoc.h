#ifndef GENBANKDOC_H
#define GENBANKDOC_H

#include "interfaces/DesignerDocItf.h"
#include "interfaces/DesignerModelItf.h"

class GENBANKDoc : public DesignerDocComponent
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit GENBANKDoc();
    ~GENBANKDoc();

    virtual extentValue checkIfFileFitsDocumentType(QFile& file);
    virtual bool loadFromFile(QFile& file);
    virtual bool saveToFile(QFile& file);

};

#endif // GENBANKDOC_H
