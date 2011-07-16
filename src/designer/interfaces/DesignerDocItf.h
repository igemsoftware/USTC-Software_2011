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

    //constructor
protected:
    //! Constructor. Called by subclasses constructors only.
    explicit DesignerDocItf();

    // data store
protected:
    DesignerModelItf * currentModel;
public:
    //! Retrieve the model object associated with this document.
    DesignerModelItf * getCurrentModel(QString defaultModel = "");

    // modified flag
public:
    //! Retrieve the modified flag associated with this document.
    bool isModified() {return modified;}
    //! Update the modified flag associated with this document.
    void setModified(bool newValue = true) {modified = newValue;}
protected:
    bool modified;

    // converting items.
public:
    enum extentValue
    {
        NOTACCEPTABLE = 0,
        INSUFFICIENTLY = 1,
        EXCESSIVELY = 2,
        EXACTLY = 3
    };
    //! Check if the file is loadable by this type of document .
    virtual extentValue checkIfFileFitsDocumentType(QFile& file) = 0;
    //! Check if the file in memory can be coverted to the specified file format.
    virtual extentValue checkIfDocCanConvertToThisType(QMetaObject& metaObject) = 0;

    //! Retrieve data from this file
    virtual bool loadFromFile(QFile& file) = 0;
    //! Dump data to this file
    virtual bool saveToFile(QFile& file) = 0;

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

Q_DECLARE_INTERFACE(DesignerDocItf, "com.ustcsoftware.Lachesis.DocumentInterface/1.0")

#endif // DESIGNERDOCITF_H
