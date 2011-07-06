#ifndef SBMLDOC_H
#define SBMLDOC_H

#include <QtScript>
#include "DesignerDocItf.h"
#include "DesignerModelItf.h"

class SBMLDoc : public DesignerDocItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SBMLDoc(DesignerMainWnd *parent = 0);
    ~SBMLDoc();

    virtual extentValue checkIfFileFitsDocumentType(QFile& file);
    virtual bool loadFromFile(QFile& file);
    virtual bool saveToFile(QFile& file);

    virtual QList<QString> getSupportedViewList() const;

    virtual extentValue checkIfDocCanConvertToThisType(QMetaObject& metaObject);

private:
signals:

public slots:

};

#endif // SBMLDOC_H
