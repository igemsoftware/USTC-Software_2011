#ifndef EMBLDOC_H
#define EMBLDOC_H

#include "interfaces/DesignerDocItf.h"
#include "interfaces/DesignerModelItf.h"

class EMBLDoc : public QObject,
                public DesignerDocItf
{
    Q_OBJECT
    Q_INTERFACES(DesignerDocItf)
public:
    Q_INVOKABLE explicit EMBLDoc();

    virtual const QMetaObject* getMetaObject() { return metaObject(); }
    virtual extentValue checkIfFileFitsDocumentType(QFile& file);

    virtual DesignerModelComponent* loadFromFile(QFile& file, DesignerDocComponent* docComp);
    virtual bool saveToFile(QFile& file, DesignerModelComponent* modelComp);
};

#endif // EMBLDOC_H
