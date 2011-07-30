#ifndef USMLDOC_H
#define USMLDOC_H

#include <QtScript>
#include "interfaces/DesignerDocItf.h"
#include "interfaces/DesignerModelItf.h"

class USMLDoc : public DesignerDocItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit USMLDoc();
    ~USMLDoc();

    virtual extentValue checkIfFileFitsDocumentType(QFile& file);
    virtual bool loadFromFile(QFile& file);
    virtual bool saveToFile(QFile& file);

    virtual extentValue checkIfDocCanConvertToThisType(QMetaObject& metaObject);

};

#endif // USMLDOC_H
