// Designer Document Common Interface

#ifndef DESIGNERDOCITF_H
#define DESIGNERDOCITF_H

#include <QObject>
#include <QFile>

class DesignerDocItf : public QObject
{
    Q_OBJECT
public:
    explicit DesignerDocItf(QObject *parent = 0);

public:
    enum extentValue
    {
        NOTACCEPTABLE = 0,
        EXACTLY = 1,
        PARTIALLY = 2,
        INSUFFICIENTLY = 3,

    };

    virtual extentValue checkIfFileFitsDocumentType(QFile& file) = 0;
    virtual bool loadFromFile(QFile& file) = 0;
    virtual bool saveToFile(QFile& file) = 0;

    virtual extentValue checkIfDocCanConvertToThisType(QMetaObject& metaObject) = 0;




signals:

public slots:

};

#endif // DESIGNERDOCITF_H
