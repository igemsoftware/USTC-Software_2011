#ifndef RSBPMLDOC_H
#define RSBPMLDOC_H

#include "interfaces/DesignerDocItf.h"

class RSBPMLDoc : public QObject,
                  public DesignerDocItf
{
    Q_OBJECT
    Q_INTERFACES(DesignerDocItf)
public:
    Q_INVOKABLE explicit RSBPMLDoc();

    virtual const QMetaObject* getMetaObject() { return metaObject(); }
    virtual extentValue checkIfFileFitsDocumentType(QFile& file);
    virtual DesignerModelComponent* loadFromFile(QFile& file, DesignerDocComponent* docComp);
    virtual bool saveToFile(QFile& file, DesignerModelComponent* modelComp);

};

#endif // RSBPMLDOC_H
