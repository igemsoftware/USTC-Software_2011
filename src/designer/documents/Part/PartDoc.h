#ifndef PARTDOC_H
#define PARTDOC_H

#include "Part.h"
#include "interfaces/DesignerDocItf.h"
#include "interfaces/DesignerModelItf.h"

class PartDoc : public DesignerDocItf
{
    Q_OBJECT
public:
    QString type;

    void detectDocType(QFile &file);
public:
    Q_INVOKABLE explicit PartDoc();
    ~PartDoc();

    virtual extentValue checkIfFileFitsDocumentType(QFile& file);
    virtual bool loadFromFile(QFile& file);
    virtual bool saveToFile(QFile& file);

};

#endif // PARTDOC_H
