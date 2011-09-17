#include <QMessageBox>

#include "common/app/DesignerApp.h"
#include "DesignerExtensionItf.h"


const QMetaObject* DesignerExtensionItf::extensionMetaObject()
{
    return NULL;
}

bool DesignerExtensionItf::initialize()
{
    return false;
}
