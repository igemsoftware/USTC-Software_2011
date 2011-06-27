#include "DesignerNetworkView.h"
#include "ui_DesignerNetworkView.h"

#include "DesignerNetworkView_SBMLHighlighter.h"


NetworkView::NetworkView(QWidget *parent) :
    DesignerViewItf(parent),
    ui(new Ui::NetworkView)
{
    ui->setupUi(this);

    sbmlHighlighter = new NetworkView_SBMLHighlighter(ui->SBMLTextEdit->document());
}

NetworkView::~NetworkView()
{
    delete ui;
    delete sbmlHighlighter;
}
