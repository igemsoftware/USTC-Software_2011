#ifndef MODELDOC_H
#define MODELDOC_H

#include <QtScript>
#include "DesignerDocItf.h"
#include "DesignerModelItf.h"

class MoDeLDoc : public DesignerDocItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit MoDeLDoc();
    ~MoDeLDoc();

    virtual extentValue checkIfFileFitsDocumentType(QFile& file);
    virtual bool loadFromFile(QFile& file);
    virtual bool saveToFile(QFile& file);

    virtual QList<QString> getSupportedViewList() const;

    virtual extentValue checkIfDocCanConvertToThisType(QMetaObject& metaObject);

private:

signals:

public slots:

};

#endif // MODELDOC_H
