#ifndef DESIGNERMODELMGR_H
#define DESIGNERMODELMGR_H

#include <QtCore>
#include "common/utils/itemregistry/ItemRegistry.h"

class DesignerModelMgr
{
public:
    DesignerModelMgr();

public:
    struct ModelItfRegistryItem
    {
        const QMetaObject* metaObject;

        ModelItfRegistryItem(const QMetaObject* m = 0)
            : metaObject(m){}
     };

    //! The archive for model dynamic loading
    typedef ItemRegistry<QString, ModelItfRegistryItem> ModelItfRegistry;

public:
    //! Initialization(dynamic loading).
    static void initializeIfNotYet();

};

#endif // DESIGNERMODELMGR_H
