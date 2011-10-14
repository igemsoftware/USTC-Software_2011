#ifndef SBOLDOC_H
#define SBOLDOC_H

#include "interfaces/DesignerDocItf.h"

class SBOLDoc : public QObject,
                public DesignerDocItf
{
    Q_OBJECT
    Q_INTERFACES(DesignerDocItf)
public:
    Q_INVOKABLE explicit SBOLDoc();

    virtual const QMetaObject* getMetaObject() { return metaObject(); }
    virtual extentValue checkIfFileFitsDocumentType(QFile& file);
    virtual DesignerModelComponent* loadFromFile(QFile& file, DesignerDocComponent* docComp);
    virtual bool saveToFile(QFile& file, DesignerModelComponent* modelComp);

};

#endif // SBOLDOC_H
