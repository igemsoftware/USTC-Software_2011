#ifndef DESIGNERDOCMGR_H
#define DESIGNERDOCMGR_H

#include <QtCore>
#include "interfaces/DesignerDocItf.h"
#include "common/utils/itemregistry/ItemRegistry.h"

class DesignerDocMgr
{
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

};

#endif // DESIGNERDOCMGR_H
