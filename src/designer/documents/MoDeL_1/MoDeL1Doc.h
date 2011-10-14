#ifndef MODEL1DOC_H
#define MODEL1DOC_H

#include <QtScript>
#include "interfaces/DesignerDocItf.h"
#include "interfaces/DesignerModelItf.h"

class MoDeL1Doc : public QObject,
                  public DesignerDocItf
{
    Q_OBJECT
    Q_INTERFACES(DesignerDocItf)
public:
    Q_INVOKABLE explicit MoDeL1Doc();

    virtual const QMetaObject* getMetaObject() { return metaObject(); }
    virtual extentValue checkIfFileFitsDocumentType(QFile& file);
    virtual DesignerModelComponent* loadFromFile(QFile& file, DesignerDocComponent* docComp);
    virtual bool saveToFile(QFile& file, DesignerModelComponent* modelComp);

};

#endif // MODEL1DOC_H
