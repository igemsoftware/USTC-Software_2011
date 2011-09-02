#include <QtGui>
#include "NetworkView.h"

#include "NetworkViewGraphicsItem.h"
#include "NetworkViewGraphicsScene.h"

#include "interfaces/DesignerModelItf.h"
#include "common/mainwnd/DesignerMainWnd.h"

#include "models/common/ModelSymbol.h"

#include "DesignerDebug.h"
#include "ui_NetworkView.h"
#include "common/panels/propertypanel/DesignerPropertiesPanelWidget.h"
#include "Layouter/lagraphlayouterthread.h"

NetworkView::NetworkView(DesignerMainWnd *mainWnd, DesignerModelItf *model) :
    DesignerViewItf(mainWnd, model),
    ui(new Ui::NetworkView)
{
    ui->setupUi(this);
//    QGridLayout* gridLayout = new QGridLayout(this);
//    gridLayout->setContentsMargins(0, 0, 0, 0);

    //ui->graphicsView = new QGraphicsView(this);
    //ui->graphicsView->setStyleSheet("QGraphicsView { border-style: none; }");
    //gridLayout->addWidget(graphicsView,1,0,1,1);
    //gridLayout->addWidget(buttons,0,1,2,2);

    NetworkViewGraphicsScene *scene = new NetworkViewGraphicsScene(ui->graphicsView);
    scene->clearScene();

    scene->loadFromModel(model);
    ui->graphicsView->setScene(scene);

    connect(scene, SIGNAL(selectionChanged()), this, SLOT(on_sceneSelectionChanged()));

    emit on_sceneSelectionChanged();
}

NetworkView::~NetworkView()
{
    delete ui;
}

void NetworkView::on_sceneSelectionChanged()
{
    QList<QGraphicsItem*> selectedItem = ui->graphicsView->scene()->selectedItems();
    if(selectedItem.count()==1)
    {
        NetworkViewGraphicsItem* item = dynamic_cast<NetworkViewGraphicsItem*>(selectedItem.first());
        if(item)
        {
            emit updateSelectedItem(item->itemObject);
            return;
        }
    }
    emit updateSelectedItem(mainWindow->getCurrentModel()->getModel());
}
