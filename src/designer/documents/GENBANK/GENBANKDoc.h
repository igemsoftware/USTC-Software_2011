#ifndef GENBANKDOC_H
#define GENBANKDOC_H

#include "interfaces/DesignerDocItf.h"
#include "interfaces/DesignerModelItf.h"

class GENBANKDoc :  public QObject,
                    public DesignerDocItf
{
    Q_OBJECT
    Q_INTERFACES(DesignerDocItf)
public:
    Q_INVOKABLE explicit GENBANKDoc();

    virtual extentValue checkIfFileFitsDocumentType(QFile& file);
    virtual DesignerModelComponent* loadFromFile(QFile& file, DesignerDocComponent* docComp);
    virtual bool saveToFile(QFile& file, DesignerModelComponent* modelComp);

};

#endif // GENBANKDOC_H
