#include "DesignerNetworkView.h"
#include "ui_DesignerNetworkView.h"

#include "DesignerNetworkView_SBMLHighlighter.h"
#include "NetworkViewGraphicsScene.h"


NetworkView::NetworkView(QWidget *parent, DesignerMainWnd *mainWnd) :
    DesignerViewItf(parent, mainWnd),
    ui(new Ui::NetworkView)
{
    ui->setupUi(this);

    sbmlHighlighter = new NetworkView_SBMLHighlighter(ui->SBMLTextEdit->document());

    NetworkViewGraphicsScene *scene = new NetworkViewGraphicsScene(ui->graphicsView);
    scene->clearScene();
    ui->graphicsView->setScene(scene);
}

NetworkView::~NetworkView()
{
    delete ui;
    delete sbmlHighlighter;
}
