#include <QMessageBox>

#include "common/app/DesignerApp.h"
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

        QString extensionPath = DesignerApp::applicationDirPath();
        if(!extensionPath.endsWith("/")) extensionPath+="/";
        extensionPath+="extensions";

        QDir extensionDir(extensionPath);
        if(!extensionDir.exists())
            extensionDir.mkpath(extensionPath);

        QFileInfoList extensionFileList = extensionDir.entryInfoList(QDir::Files);

        for(int i=0;i<extensionFileList.count();i++)
        {
            QPluginLoader loader(extensionFileList[i].absoluteFilePath());
            QObject* extensionObject;
            DesignerExtensionItf* extensionObjectItf;
            if(!(extensionObject = loader.instance())||
                    !(extensionObjectItf = qobject_cast<DesignerExtensionItf*>(extensionObject)))
            {
                QMessageBox msgBox(QMessageBox::NoIcon,
                                   tr("Lachesis Designer"),
                                   tr("Error loading extension '%1'. All its functionality will be unusable.")
                                        .arg(extensionFileList[i].absoluteFilePath())
                            );
                msgBox.exec();
            }
            else
            {
                loader.unload();
            }
        }
    }
}


DesignerExtensionItf::DesignerExtensionItf(QObject *parent) :
    QObject(parent)
{
}
