#include "common/app/DesignerApp.h"
#include "interfaces/DesignerInterface.h"

#include "DesignerExtensionMgr.h"

#include "interfaces/DesignerExtensionItf.h"

#define LACHESIS_DECLARE_EXTENSION(className) \
    DesignerExtensionMgr::ExtensionItfRegistry::ItemRegistryInlineAdd extreg_##className (QString( #className ), \
    DesignerExtensionMgr::ExtensionItfRegistryItem(& className ::staticMetaObject))

void DesignerExtensionMgr::initializeIfNotYet()
{
    static bool initialized = false;
    if(!initialized)
    {
        initialized = true;

        QString extensionPath = DesignerApp::applicationDirPath();
        if(!extensionPath.endsWith("/")) extensionPath+="/";
        extensionPath+="extensions";

        QDir extensionDir(extensionPath);
        if(!extensionDir.exists())
            extensionDir.mkpath(extensionPath);

        QFileInfoList extensionFileList = extensionDir.entryInfoList(QDir::Files);

        for(int i=0;i<extensionFileList.count();i++)
        {
            if(extensionFileList[i].absoluteFilePath().endsWith(".a")) continue;
            QPluginLoader loader(extensionFileList[i].absoluteFilePath());
            QObject* extensionObject;
            DesignerExtensionItf* extensionObjectItf;
            if(!(extensionObject = loader.instance())||
                    !(extensionObjectItf = qobject_cast<DesignerExtensionItf*>(extensionObject)))
            {
                QMessageBox msgBox(QMessageBox::NoIcon,
                                   QObject::tr("Lachesis Designer"),
                                   QObject::tr("Error loading extension '%1'. All its functionality will be unusable.")
                                        .arg(extensionFileList[i].absoluteFilePath())
                            );
                msgBox.exec();
            }
            else
            {
                ExtensionItfRegistry::ItemRegistryInlineAdd(loader.fileName(), extensionObjectItf->extensionMetaObject());
                extensionObjectItf->initialize();
                loader.unload();
            }
        }
    }
}
