#ifndef SBMLDOC_H
#define SBMLDOC_H

#include <QtScript>
#include "interfaces/DesignerDocItf.h"
#include "interfaces/DesignerModelItf.h"

class SBMLDoc : public DesignerDocItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SBMLDoc();
    ~SBMLDoc();

    virtual extentValue checkIfFileFitsDocumentType(QFile& file);
    virtual bool loadFromFile(QFile& file);
    virtual bool saveToFile(QFile& file);

    virtual extentValue checkIfDocCanConvertToThisType(QMetaObject& metaObject);

};

#endif // SBMLDOC_H
