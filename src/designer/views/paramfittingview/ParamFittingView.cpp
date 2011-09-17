#include "ParamFittingView.h"
#include "ui_ParamFittingView.h"

ParamFittingView::ParamFittingView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParamFittingView)
{
    ui->setupUi(this);
}

ParamFittingView::~ParamFittingView()
{
    delete ui;
}
