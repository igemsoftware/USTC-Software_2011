#include <QtGui>
#include "NetworkView.h"

#include "NetworkViewGraphicsScene.h"

#include "DesignerModelItf.h"
#include "DesignerMainWnd.h"

#include "models/common/ModelSymbol.h"

#include "DesignerDebug.h"

#include "common/panels/propertypanel/DesignerPropertiesPanelWidget.h"

NetworkView::NetworkView(DesignerMainWnd *mainWnd) :
    DesignerViewItf(mainWnd)
{

    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    QGraphicsView* graphicsView = new QGraphicsView(this);
    graphicsView->setStyleSheet("QGraphicsView { border-style: none; }");
    gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

    NetworkViewGraphicsScene *scene = new NetworkViewGraphicsScene(graphicsView);
    scene->clearScene();

    scene->loadFromModel(mainWindow->getCurrentDoc("SBMLDoc")->getCurrentModel("ReactionNetworkModel"));

    graphicsView->setScene(scene);

    ((DesignerPropertiesPanelWidget*)mainWindow->getPanelWidget("PropertiesPanel"))->updateTarget(mainWindow->getCurrentDoc("SBMLDoc")->getCurrentModel("ReactionNetworkModel")->getEngine()->globalObject().property("*model*"));
}
