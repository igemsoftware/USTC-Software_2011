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
        QScriptValue parts=model->getModel();
        int length=parts.property("length").toInt32();
        QStringListModel* slm = new QStringListModel(this);
        QStringList* sl = new QStringList();
        for(int i=0;i<length;i++)
        {
            sl->append(parts.property(i).property("*partsregistry.org*").property("part_name").toString());
        }
        slm->setStringList(*sl);
        ui->listView->setModel(slm);

        ui->textEdit->setText("Description&Features:"+parts.property(0).property("*partsregistry.org*").property("part_descr").toString()+parts.property(0).property("partfeatures").toString());
        ui->textEdit_seq->setText(parts.property(0).property("partsequence").toString());
        ui->partNameEdit->setText(model->getModel().property(0).property("*partsregistry.org*").property("part_name").toString());
        ui->label_length->setText(QString::number(model->getModel().property(0).property("partsequence").toString().length()));
        QString t=parts.property(0).property("*partsregistry.org*").property("part_parameters").property(0).property("parameter_value").toString();
        if(t!="")
            ui->lineEdit_2->setText(t);
        t=parts.property(0).property("*partsregistry.org*").property("part_parameters").property(0).property("parameter_biology").toString();
        if(t!="")
            ui->lineEdit->setText(t);
        QPixmap pic(":/designer/partview/icon_"+parts.property(0).property("*partsregistry.org*").property("part_type").toString().toLower()+".png");
        if(!pic.isNull())
            ui->label_image->setPixmap(pic);
    }

}

PartView::~PartView()
{
    delete ui;
}

void PartView::on_listView_clicked(QModelIndex index)
{
    int i=index.row();
    QScriptValue part=this->model->getModel().property(i);
    ui->textEdit->setText("Description&Features:"+part.property("*partsregistry.org*").property("part_descr").toString()+part.property("partfeatures").toString());
    ui->textEdit_seq->setText(part.property("partsequence").toString());
    ui->partNameEdit->setText(model->getModel().property(0).property("*partsregistry.org*").property("part_name").toString());
    ui->label_length->setText(QString::number(model->getModel().property(0).property("partsequence").toString().length()));
    QString t=part.property("*partsregistry.org*").property("part_parameters").property(0).property("parameter_value").toString();
    if(t!="")
        ui->lineEdit_2->setText(t);
    t=part.property("*partsregistry.org*").property("part_parameters").property(0).property("parameter_biology").toString();
    if(t!="")
        ui->lineEdit->setText(t);

    QPixmap pic(":/designer/partview/icon_"+part.property("*partsregistry.org*").property("part_type").toString().toLower()+".png");
    if(!pic.isNull())
        ui->label_image->setPixmap(pic);
}
