#ifndef DESIGNERDOCCOMPONENT_H
#define DESIGNERDOCCOMPONENT_H

#include "DesignerDocItf.h"
#include <QtNetwork>

#include "common/componentmgr/DesignerDocMgr.h"

class DesignerDocComponent : public QObject
{
    Q_OBJECT

    //constructor
public:
    //! Constructor.
    explicit DesignerDocComponent(DesignerDocItf* = 0);

    // data store
protected:
    DesignerModelComponent * currentModel;
public:
    //! Retrieve the model object associated with this document.
    DesignerModelComponent * getCurrentModel(QString defaultModel = "");

    // network manager
    QNetworkAccessManager* netmanager;

    // specialized document interface
    DesignerDocItf* interface;

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
    typedef DesignerDocItf::extentValue extentValue;

    static bool fitIsBetterThan(extentValue a, extentValue b)
    {
        if(a!=DesignerDocItf::NOTACCEPTABLE && b==DesignerDocItf::NOTACCEPTABLE) return TRUE;
        if(a==DesignerDocItf::EXACTLY       && b!=DesignerDocItf::NOTACCEPTABLE) return TRUE;
        if(a==DesignerDocItf::EXCESSIVELY   && b==DesignerDocItf::INSUFFICIENTLY) return TRUE;
        return FALSE;
    }


    friend class DesignerDocMgr;
public slots:

};

#endif // DESIGNERDOCCOMPONENT_H
