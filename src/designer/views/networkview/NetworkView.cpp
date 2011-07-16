#include <QtGui>
#include "NetworkView.h"

#include "NetworkViewGraphicsItem.h"
#include "NetworkViewGraphicsScene.h"

#include "interfaces/DesignerModelItf.h"
#include "DesignerMainWnd.h"

#include "models/common/ModelSymbol.h"

#include "DesignerDebug.h"

#include "common/panels/propertypanel/DesignerPropertiesPanelWidget.h"

NetworkView::NetworkView(DesignerMainWnd *mainWnd) :
    DesignerViewItf(mainWnd)
{

    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    graphicsView = new QGraphicsView(this);
    graphicsView->setStyleSheet("QGraphicsView { border-style: none; }");
    gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

    NetworkViewGraphicsScene *scene = new NetworkViewGraphicsScene(graphicsView);
    scene->clearScene();

    scene->loadFromModel(mainWindow->getCurrentModel());

    graphicsView->setScene(scene);

    connect(scene, SIGNAL(selectionChanged()), this, SLOT(on_sceneSelectionChanged()));
    connect(this, SIGNAL(updateSelectedItem(QScriptValue)),  mainWindow->getPanelWidget("PropertiesPanel"), SLOT(updateTarget(QScriptValue)));

    emit on_sceneSelectionChanged();
}

void NetworkView::on_sceneSelectionChanged()
{
    QList<QGraphicsItem*> selectedItem = graphicsView->scene()->selectedItems();
    if(selectedItem.count()==1)
    {
        NetworkViewGraphicsItem* item = dynamic_cast<NetworkViewGraphicsItem*>(selectedItem.first());
        if(item)
        {
            emit updateSelectedItem(item->itemObject);
            return;
        }
    }
    emit updateSelectedItem(mainWindow->getCurrentModel()->getEngine()->globalObject().property("*model*"));
}
