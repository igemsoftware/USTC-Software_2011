#ifndef DESIGNERDOCCOMPONENT_H
#define DESIGNERDOCCOMPONENT_H

#include "DesignerDocItf.h"
#include <QtNetwork>

#include "common/componentmgr/DesignerDocMgr.h"

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

    // network manager
    QNetworkAccessManager* netmanager;


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

public:
    //! Retrieve data from file on disk.
    bool loadFromDiskFile(QString fileName);
    //! Dump data to file on disk.
    bool saveToDiskFile(QString fileName);
    //! Dump data to the previous file.
    bool updateFile();

public:
    bool loadFromUrl(QString url);
public slots:
    void loadFromUrlFinished(QNetworkReply* reply);

public:
    static bool fitIsBetterThan(extentValue a, extentValue b)
    {
        if(a!=NOTACCEPTABLE && b==NOTACCEPTABLE) return TRUE;
        if(a==EXACTLY && b!=NOTACCEPTABLE) return TRUE;
        if(a==EXCESSIVELY && b==INSUFFICIENTLY) return TRUE;
        return FALSE;
    }


    friend class DesignerDocMgr;
public slots:

};

#endif // DESIGNERDOCCOMPONENT_H
