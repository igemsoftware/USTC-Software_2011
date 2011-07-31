//! \file DesignerDocItf.h
//! Lachesis Designer Document Common Interface

#ifndef DESIGNERDOCITF_H
#define DESIGNERDOCITF_H

#include <QtCore>
#include "common/utils/itemregistry/ItemRegistry.h"
#include "DesignerDebug.h"

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
    bool isModified() const {return modified;}
    //! Update the modified flag associated with this document.
    void setModified(bool newValue = true) {modified = newValue;}
protected:
    bool modified;

    // readonly flag
public:
    bool isReadOnly() const { return readOnly;}
protected:
    bool readOnly;

    // storage
protected:
    QFile file;
public:
    QString getFileName() {return file.fileName();}

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
    //! \bug this should be moved to Model.
    // virtual extentValue checkIfDocCanConvertToThisType(QMetaObject& metaObject) = 0;

    //! Retrieve data from this file
    virtual bool loadFromFile(QFile& file) = 0;
    //! Dump data to this file
    virtual bool saveToFile(QFile& file) = 0;
    //! Dump data to the previous file.
    bool saveToFile();
public:
    struct DocItfRegistryItem
    {
        const QMetaObject*  metaObject;
        bool  supportSave;
        QString filterText;

        DocItfRegistryItem(const QMetaObject* m = 0, bool s = false, QString f = QString())
            : metaObject(m), supportSave(s), filterText(f){}
     };

    //! The archive for document dynamic loading
    typedef ItemRegistry<QString, DocItfRegistryItem> DocItfRegistry;
public:
    //! Initialization(dynamic loading).
    static void initializeIfNotYet();

public:
    static DesignerDocItf* createEmptyDoc(QString docName);
    static bool isDocTypeSaveSupported(QString docName);
    static QString getDocTypeFilter(QString docName);

    static const QMetaObject* getBestFitDocumentTypeForFile(QString pathName);


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
