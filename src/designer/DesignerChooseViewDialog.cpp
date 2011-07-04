#include "DesignerChooseViewDialog.h"
#include "ui_DesignerChooseViewDialog.h"

#include "DesignerViewItf.h"

ChooseViewDialog::ChooseViewDialog(QWidget *parent, QList<QString> viewList) :
    QDialog(parent),
    ui(new Ui::ChooseViewDialog)
{
    ui->setupUi(this);
    if(viewList.count())
    {
        for(int i = 0; i < viewList.count(); i ++)
        {
            ui->listViews->addItem(DesignerViewItf::getViewTitleByName(viewList[i]));
        }
        ui->listViews->setCurrentRow(0);
    }
}

ChooseViewDialog::~ChooseViewDialog()
{
    delete ui;
}

int ChooseViewDialog::getChoosenViewIndex()
{
    return ui->listViews->currentRow();
}
