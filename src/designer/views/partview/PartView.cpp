#include <QtScript>

#include "interfaces/DesignerViewItf.h"
#include "interfaces/DesignerModelItf.h"

#include "PartView.h"
#include "ui_partview.h"
#include "DesignerMainWnd.h"

PartView::PartView(DesignerMainWnd *mainWnd, DesignerModelItf *model) :
    DesignerViewItf(mainWnd, model),
    ui(new Ui::PartView)
{
    ui->setupUi(this);

    connect(this, SIGNAL(updateSelectedItem(QScriptValue)),  mainWindow->getPanelWidget("PropertiesPanel"), SLOT(updateTarget(QScriptValue)));

    emit updateSelectedItem(model->getModel());

    {
        ui->partNameEdit->setText(model->getModel().property(0).property("*partsregistry.org*").property("part_name").toString());
        ui->partNameEdit->setText(model->getModel().property(0).property("*partsregistry.org*").property("twins").property("length").toString());
    }

}

PartView::~PartView()
{
    delete ui;
}
