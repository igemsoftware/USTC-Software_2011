#include "DesignerBehaviorView.h"
#include "ui_DesignerBehaviorView.h"

BehaviorView::BehaviorView(QWidget *parent) :
    DesignerViewItf(parent),
    ui(new Ui::BehaviorView)
{
    ui->setupUi(this);
}

BehaviorView::~BehaviorView()
{
    delete ui;
}
