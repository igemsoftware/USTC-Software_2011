#ifndef FASTADOC_H
#define FASTADOC_H

#include "interfaces/DesignerDocItf.h"
#include "interfaces/DesignerModelItf.h"

class FASTADoc : public QObject,
                 public DesignerDocItf
{
    Q_OBJECT
    Q_INTERFACES(DesignerDocItf)
public:
    Q_INVOKABLE explicit FASTADoc();

    virtual const QMetaObject* getMetaObject() { return metaObject(); }
    virtual extentValue checkIfFileFitsDocumentType(QFile& file);
    virtual DesignerModelComponent* loadFromFile(QFile& file, DesignerDocComponent* docComp);
    virtual bool saveToFile(QFile& file, DesignerModelComponent* modelComp);

};

#endif // FASTADOC_H
