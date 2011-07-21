#ifndef RSBPMLDOC_H
#define RSBPMLDOC_H

#include "interfaces/DesignerDocItf.h"

class RSBPMLDoc : public DesignerDocItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit RSBPMLDoc();
    ~RSBPMLDoc();

    virtual extentValue checkIfFileFitsDocumentType(QFile& file);
    virtual bool loadFromFile(QFile& file);
    virtual bool saveToFile(QFile& file);

signals:

public slots:

};

#endif // RSBPMLDOC_H
