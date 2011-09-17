#include "common/mainwnd/DesignerMainWnd.h"

#include "common/utils/itemregistry/ItemRegistry.h"
#include "DesignerViewItf.h"

DesignerViewComponent::DesignerViewComponent(DesignerMainWnd* mainWnd, DesignerModelComponent* model)
    :mainWindow(mainWnd), currentModel(model)
{
    connect(this, SIGNAL(updateSelectedItem(QScriptValue)),  mainWindow->getPanelWidget("PropertiesPanel"), SLOT(updateTarget(QScriptValue)));
}



