#include "interfaces/DesignerViewItf.h"

#include "PartView.h"
#include "ui_partview.h"
#include "DesignerMainWnd.h"

PartView::PartView(DesignerMainWnd *mainWnd) :
    DesignerViewItf(mainWnd),
    ui(new Ui::PartView)
{
    ui->setupUi(this);
}

PartView::~PartView()
{
    delete ui;
}
