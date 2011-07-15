#include "partsview.h"
#include "ui_partsview.h"

PartsView::PartsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PartsView)
{
    ui->setupUi(this);
}

PartsView::~PartsView()
{
    delete ui;
}
