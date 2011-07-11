// Designer Document Common Interface

#ifndef DESIGNERDOCITF_H
#define DESIGNERDOCITF_H

#include <QObject>
#include <QFile>

class DesignerMainWnd;
class DesignerModelItf;

class DesignerDocItf : public QObject
{
    Q_OBJECT
protected:
    DesignerModelItf * currentModel;
    bool modified;
public:
    DesignerModelItf * getCurrentModel(QString defaultModel = "");

    bool isModified() {return modified;}
    void setModified(bool newValue = true) {modified = newValue;}

public:
    explicit DesignerDocItf();
	
public:
    enum extentValue
    {
        NOTACCEPTABLE = 0,
        INSUFFICIENTLY = 1,
        EXCESSIVELY = 2,
        EXACTLY = 3
    };
    virtual extentValue checkIfFileFitsDocumentType(QFile& file) = 0;

    virtual bool loadFromFile(QFile& file) = 0;
    virtual bool saveToFile(QFile& file) = 0;

    virtual QList<QString> getSupportedViewList() const = 0;

    virtual extentValue checkIfDocCanConvertToThisType(QMetaObject& metaObject) = 0;


public:

    static DesignerDocItf* createEmptyDoc(QString docName);

    static QMetaObject* getFileFitsDocumentTypesStatus(QString pathName);


private:
    static bool fitIsBetterThan(extentValue a, extentValue b)
    {
        if(a!=NOTACCEPTABLE && b==NOTACCEPTABLE) return TRUE;
        if(a==EXACTLY && b!=NOTACCEPTABLE) return TRUE;
        if(a==EXCESSIVELY && b==INSUFFICIENTLY) return TRUE;
        return FALSE;
    }


signals:

public slots:

};

#endif // DESIGNERDOCITF_H
