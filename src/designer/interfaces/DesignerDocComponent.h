#ifndef DESIGNERDOCCOMPONENT_H
#define DESIGNERDOCCOMPONENT_H

#include "DesignerDocItf.h"

class DesignerDocComponent : public QObject,
                             public DesignerDocItf
{
    Q_OBJECT
    Q_INTERFACES(DesignerDocItf)

    //constructor
protected:
    //! Constructor. Called by subclasses constructors only.
    explicit DesignerDocComponent();

    // data store
protected:
    DesignerModelComponent * currentModel;
public:
    //! Retrieve the model object associated with this document.
    DesignerModelComponent * getCurrentModel(QString defaultModel = "");

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
    typedef DesignerDocItf::extentValue extentValue;
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
    static DesignerDocComponent* createEmptyDoc(QString docName, DesignerModelComponent* model = NULL);
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

#endif // DESIGNERDOCCOMPONENT_H
