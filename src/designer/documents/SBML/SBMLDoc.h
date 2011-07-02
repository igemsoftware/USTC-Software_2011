#ifndef SBMLDOC_H
#define SBMLDOC_H

#include <QtScript>
#include "DesignerDocItf.h"
#include "DesignerModelItf.h"

class SBMLDoc : public DesignerDocItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SBMLDoc(QObject *parent = 0);
    ~SBMLDoc();

    virtual extentValue checkIfFileFitsDocumentType(QFile& file);
    virtual bool loadFromFile(QFile& file);
    virtual bool saveToFile(QFile& file);

    virtual extentValue checkIfDocCanConvertToThisType(QMetaObject& metaObject);

private:
    DesignerModelItf* currentModel;
signals:

public slots:

};

#endif // SBMLDOC_H
