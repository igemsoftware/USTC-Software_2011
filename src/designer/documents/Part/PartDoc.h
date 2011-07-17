#ifndef PARTDOC_H
#define PARTDOC_H

#include "Part.h"
#include "interfaces/DesignerDocItf.h"
#include "interfaces/DesignerModelItf.h"

class PartDoc : public DesignerDocItf
{
public:
    QString type;
    QList<Part> *parts;
    QList<QString> *content;
public:
    Q_INVOKABLE explicit PartDoc();
    ~PartDoc();

    virtual extentValue checkIfFileFitsDocumentType(QFile& file);
    virtual bool loadFromFile(QFile& file);
    virtual bool saveToFile(QFile& file);

    virtual extentValue checkIfDocCanConvertToThisType(QMetaObject& metaObject);
};

#endif // PARTDOC_H
