#ifndef SBOLDOC_H
#define SBOLDOC_H

#include "interfaces/DesignerDocItf.h"

class SBOLDoc : public DesignerDocItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SBOLDoc();
    ~SBOLDoc();

    virtual extentValue checkIfFileFitsDocumentType(QFile& file);
    virtual bool loadFromFile(QFile& file);
    virtual bool saveToFile(QFile& file);

signals:

public slots:

};

#endif // SBOLDOC_H
