#ifndef MODEL1DOC_H
#define MODEL1DOC_H

#include <QtScript>
#include "interfaces/DesignerDocItf.h"
#include "interfaces/DesignerModelItf.h"

class MoDeL1Doc : public DesignerDocComponent
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit MoDeL1Doc();
    ~MoDeL1Doc();

    virtual extentValue checkIfFileFitsDocumentType(QFile& file);
    virtual bool loadFromFile(QFile& file);
    virtual bool saveToFile(QFile& file);

    virtual extentValue checkIfDocCanConvertToThisType(QMetaObject& metaObject);

};

#endif // MODEL1DOC_H
