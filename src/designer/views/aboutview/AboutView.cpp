#include "common/mainwnd/DesignerMainWnd.h"

#include "ui_AboutView.h"
#include "AboutView.h"

AboutView::AboutView(DesignerMainWnd *mainWnd, DesignerModelComponent *model) :
    DesignerViewComponent(mainWnd, model),
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
