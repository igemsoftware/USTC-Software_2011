#include "interfaces/DesignerViewItf.h"

#include "PartView.h"
#include "ui_partview.h"
#include "DesignerMainWnd.h"

LACHESIS_DECLARE_VIEW(PartView, "Part View");

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
