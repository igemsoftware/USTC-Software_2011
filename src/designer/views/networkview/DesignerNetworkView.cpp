#include "DesignerNetworkView.h"
#include "ui_DesignerNetworkView.h"

#include "DesignerNetworkView_SBMLHighlighter.h"
#include "NetworkViewGraphicsScene.h"

#include "DesignerModelItf.h"
#include "DesignerMainWnd.h"

#include "models/common/ModelSymbol.h"

#include "DesignerDebug.h"

NetworkView::NetworkView(QWidget *parent, DesignerMainWnd *mainWnd) :
    DesignerViewItf(parent, mainWnd),
    ui(new Ui::NetworkView)
{
    ui->setupUi(this);


    NetworkViewGraphicsScene *scene = new NetworkViewGraphicsScene(ui->graphicsView);
    scene->clearScene();

    scene->loadFromModel(mainWindow->getCurrentDoc("SBMLDoc")->getCurrentModel("ReactionNetworkModel"));

    ui->graphicsView->setScene(scene);

    //
    sbmlHighlighter = new NetworkView_SBMLHighlighter(ui->SBMLTextEdit->document());

}

NetworkView::~NetworkView()
{
    delete ui;
    delete sbmlHighlighter;
}
