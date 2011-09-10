#ifndef DESIGNERVIEWMGR_H
#define DESIGNERVIEWMGR_H

#include <QtCore>
#include "interfaces/DesignerViewItf.h"
#include "common/utils/itemregistry/ItemRegistry.h"

class DesignerViewMgr
{
public:
    DesignerViewMgr();


public:
    struct ViewItfRegistryItem
    {
        const QMetaObject*  metaObject;
        QString             viewTitle;
        QString             defaultModelName;

        ViewItfRegistryItem(const QMetaObject* m = 0,QString v = "Invalid", QString d = "")
            : metaObject(m), viewTitle(v), defaultModelName(d) {}
     };

    //! The archive for view dynamic loading
    typedef ItemRegistry<QString, ViewItfRegistryItem> ViewItfRegistry;
public:
    //! Initialization(dynamic loading).
    static void initializeIfNotYet();

};

#endif // DESIGNERVIEWMGR_H
