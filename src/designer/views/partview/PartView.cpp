#include "interfaces/DesignerViewItf.h"

#include "PartView.h"
#include "ui_partview.h"
#include "DesignerMainWnd.h"

PartView::PartView(DesignerMainWnd *mainWnd, DesignerModelItf *model) :
    DesignerViewItf(mainWnd, model),
    ui(new Ui::PartView)
{
    ui->setupUi(this);
}

PartView::~PartView()
{
    delete ui;
}
