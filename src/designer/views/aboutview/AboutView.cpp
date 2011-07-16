#include "DesignerMainWnd.h"

#include "ui_AboutView.h"
#include "AboutView.h"

LACHESIS_DECLARE_VIEW(AboutView, "About");

AboutView::AboutView(DesignerMainWnd *mainWnd) :
    DesignerViewItf(mainWnd),
    ui(new Ui::AboutView)
{
    ui->setupUi(this);
    mainWindow->removeTabWithClass("AboutView");
}

AboutView::~AboutView()
{
    delete ui;
}

void AboutView::on_closeButton_clicked()
{
    mainWindow->removeTabWithClass("AboutView");
}
