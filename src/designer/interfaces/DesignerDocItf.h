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

    // readonly flag
public:
    bool isReadOnly() const { return readOnly;}
protected:
    bool readOnly;

    // storage    
protected:
    QFileInfo documentFileInfo;
public:
    QFileInfo& getDocumentFileInfo() {return documentFileInfo;}

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

protected:
    //! Retrieve data from this file. (implemented by subclasses)
    virtual bool loadFromFile(QFile& file) = 0;
    //! Dump data to this file. (implemented by subclasses)
    virtual bool saveToFile(QFile& file) = 0;
public:
    //! Retrieve data from file on disk.
    bool loadFromDiskFile(QString fileName);
    //! Dump data to file on disk.
    bool saveToDiskFile(QString fileName);
    //! Dump data to the previous file.
    bool updateFile();

public:
    struct DocItfRegistryItem
    {
        const QMetaObject*  metaObject;
        bool  supportSave;
        QString titleText;
        QString filterText;

        DocItfRegistryItem(const QMetaObject* m = 0, bool s = false, QString t = QString(), QString f = QString())
            : metaObject(m), supportSave(s), titleText(t), filterText(f){}
     };

    //! The archive for document dynamic loading
    typedef ItemRegistry<QString, DocItfRegistryItem> DocItfRegistry;
public:
    //! Initialization(dynamic loading).
    static void initializeIfNotYet();

public:
    static DesignerDocItf* createEmptyDoc(QString docName, DesignerModelItf* model = NULL);
    static bool isDocTypeSaveSupported(QString docName);
    static QString getDocTypeTitle(QString docName);
    static QString getDocTypeFilter(QString docName);
    static QStringList getDocTypeList();

    static const QMetaObject* getBestFitDocumentTypeForFile(QString pathName);


private:
    static bool fitIsBetterThan(extentValue a, extentValue b)
    {
        if(a!=NOTACCEPTABLE && b==NOTACCEPTABLE) return TRUE;
        if(a==EXACTLY && b!=NOTACCEPTABLE) return TRUE;
        if(a==EXCESSIVELY && b==INSUFFICIENTLY) return TRUE;
        return FALSE;
    }



public slots:

};

Q_DECLARE_INTERFACE(DesignerDocItf, "com.ustcsoftware.Lachesis.DocumentInterface/1.0")

#endif // DESIGNERDOCITF_H
