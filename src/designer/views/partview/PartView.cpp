#include <QtScript>

#include "interfaces/DesignerViewItf.h"
#include "interfaces/DesignerModelItf.h"

#include "PartView.h"
#include "DesignerMainWnd.h"

PartView::PartView(DesignerMainWnd *mainWnd, DesignerModelItf *model) :
    DesignerViewItf(mainWnd, model),
    ui(new Ui::PartView)
{
    ui->setupUi(this);
    this->model=model;

    connect(this, SIGNAL(updateSelectedItem(QScriptValue)),  mainWindow->getPanelWidget("PropertiesPanel"), SLOT(updateTarget(QScriptValue)));

    emit updateSelectedItem(model->getModel());

    {
        QScriptValue parts=model->getEngine()->globalObject().property("parts");
        int length=parts.property("length").toInt32();
        QStringListModel* slm = new QStringListModel(this);
        QStringList* sl = new QStringList();
        for(int i=0;i<length;i++)
        {
            sl->append(parts.property(i).property("acc").toString());
        }
        slm->setStringList(*sl);
        ui->listView->setModel(slm);        
        ui->textEdit->setText("Description:"+parts.property(0).property("descr").toString());
        ui->textEdit_seq->setText(parts.property(0).property("sequence").toString());

        ui->partNameEdit->setText(model->getModel().property(0).property("*partsregistry.org*").property("part_name").toString());
        ui->label_length->setText(model->getModel().property(0).property("*partsregistry.org*").property("twins").property("length").toString());
    }

}

PartView::~PartView()
{
    delete ui;
}

void PartView::on_listView_clicked(QModelIndex index)
{
    int i=index.row();
    QScriptValue part=this->model->getEngine()->globalObject().property("parts").property(i);
    ui->partNameEdit->setText(part.property("acc").toString());
    ui->label_length->setText(part.property("len").toString());
    ui->textEdit->setText("Description:"+part.property("descr").toString());
    ui->textEdit_seq->setText(part.property("sequence").toString());
}
