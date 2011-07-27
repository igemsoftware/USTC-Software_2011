#include "DesignerExtensionItf.h"

#define LACHESIS_DECLARE_EXTENSION(className) \
    DesignerExtensionItf::ExtensionItfRegistry::ItemRegistryInlineAdd extreg_##className (QString( #className ), \
    DesignerExtensionItf::ExtensionItfRegistryItem(& className ::staticMetaObject))

void DesignerExtensionItf::initializeIfNotYet()
{
    static bool initialized = false;
    if(!initialized)
    {
        initialized = true;
    }
}


DesignerExtensionItf::DesignerExtensionItf(QObject *parent) :
    QObject(parent)
{
}
