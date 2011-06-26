#include "DesignerAssemblyView.h"
#include "ui_DesignerAssemblyView.h"

AssemblyView::AssemblyView(QWidget *parent) :
    DesignerViewItf(parent),
    ui(new Ui::AssemblyView)
{
    ui->setupUi(this);
}

AssemblyView::~AssemblyView()
{
    delete ui;
}
