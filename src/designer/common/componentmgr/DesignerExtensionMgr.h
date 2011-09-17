#ifndef DESIGNEREXTENSIONMGR_H
#define DESIGNEREXTENSIONMGR_H

#include <QtCore>
#include "common/utils/itemregistry/ItemRegistry.h"

class DesignerExtensionMgr
{
public:
    struct ExtensionItfRegistryItem
    {
        const QMetaObject* metaObject;

        ExtensionItfRegistryItem(const QMetaObject* m = 0)
            : metaObject(m){}
     };

    //! The archive for extension dynamic loading
    typedef ItemRegistry<QString, ExtensionItfRegistryItem> ExtensionItfRegistry;

public:
    //! Initialization(dynamic loading).
    static void initializeIfNotYet();

};

/*
    enum ExtensionDisplayLevel
    {
        DisplayAsStandaloneFrame,
        DisplayAsModalDialog,
        DisplayAsModelessDialog,
        DisplayAsView,
        DisplayAsButton,
        DisplayAsNothing
    };

    enum ExtensionInvokeType
    {
        NewModel           = 1,
        NewDocument        = 2,
        NewView            = 4,
        NewMenuItem        = 8,
        NewToolBarButton   = 16,
        NewViewHook        = 32
    };


  */
#endif // DESIGNEREXTENSIONMGR_H
