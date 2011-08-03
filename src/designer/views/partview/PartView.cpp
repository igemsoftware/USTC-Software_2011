#include <QtScript>

#include "interfaces/DesignerViewItf.h"
#include "interfaces/DesignerModelItf.h"

#include "PartView.h"
#include "DesignerMainWnd.h"
#include "documents/common/designerpartdocparser/DesignerPartDocParser.h"

PartView::PartView(DesignerMainWnd *mainWnd, DesignerModelItf *model) :
    DesignerViewItf(mainWnd, model),
    ui(new Ui::PartView)
{
    ui->setupUi(this);
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
        ui->textEdit->setText(parts.property(0).property("*partsregistry.org*").property("part_descr").toString());
        ui->textEdit_seq->setText(parts.property(0).property("partsequence").toString());
        ui->partNameEdit->setText(model->getModel().property(0).property("*partsregistry.org*").property("part_name").toString());
        ui->label_length->setText(QString::number(model->getModel().property(0).property("partsequence").toString().length()));
        QString t=parts.property(0).property("*partsregistry.org*").property("part_parameters").property(0).property("parameter_value").toString();
        if(t!="")
            ui->lineEdit_2->setText(t);
        t=parts.property(0).property("*partsregistry.org*").property("part_parameters").property(1).property("parameter_value").toString();
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
    QScriptValue part=this->currentModel->getModel().property(i);
    ui->textEdit->setText(part.property("*partsregistry.org*").property("part_descr").toString());
    ui->textEdit_seq->setText(part.property("partsequence").toString());
    ui->partNameEdit->setText(part.property("*partsregistry.org*").property("part_name").toString());
    ui->label_length->setText(QString::number(part.property("partsequence").toString().length()));
    QString t=part.property("*partsregistry.org*").property("part_parameters").property(0).property("parameter_value").toString();
    if(t!="")
        ui->lineEdit_2->setText(t);
    t=part.property("*partsregistry.org*").property("part_parameters").property(1).property("parameter_value").toString();
    if(t!="")
        ui->lineEdit->setText(t);

    QPixmap pic(":/designer/partview/icon_"+part.property("*partsregistry.org*").property("part_type").toString().toLower()+".png");
    if(!pic.isNull())
        ui->label_image->setPixmap(pic);
}

void PartView::on_pushButton_clicked()
{
    int i=ui->listView->currentIndex().row();
    QScriptValue part;
    {
        if(i==-1)
            i++;
        part=this->currentModel->getModel().property(i).property("*partsregistry.org*");
        part.setProperty("part_name",ui->partNameEdit->text());
        QStringListModel* slm=dynamic_cast<QStringListModel *>(ui->listView->model());
        QStringList sl=slm->stringList();
        sl[i]=ui->partNameEdit->text();
        slm->setStringList(sl);
        ui->listView->setModel(slm);
    }
    {
        if(i==-1)
            i++;
        QScriptValue parameter=this->currentModel->getModel().property(i).property("*partsregistry.org*").property("part_parameters").property(1);
        if(!parameter.isNull())
        {
            parameter.setProperty("parameter_value",ui->lineEdit->text());
        }
    }
    {
        if(i==-1)
            i++;
        QScriptValue parameter=this->currentModel->getModel().property(i).property("*partsregistry.org*").property("part_parameters").property(0);
        if(!parameter.isNull())
        {
            parameter.setProperty("parameter_value",ui->lineEdit_2->text());
        }
    }
    {
        if(i==-1)
            i++;
        part=this->currentModel->getModel().property(i).property("*partsregistry.org*");
        part.setProperty("part_descr",ui->textEdit->toPlainText());
    }
    {
        if(i==-1)
            i++;
        part=this->currentModel->getModel().property(i);
        QString newsq=DesignerPartDocParser::generateSequence(ui->textEdit_seq->toPlainText());
        part.setProperty("partsequence",newsq);
        ui->label_length->setText(QString::number(newsq.length()));
    }

    //! \bug This is test code. Will be handled in a more elegant way in the future -CrLF0710
    mainWindow->getCurrentModel()->setModified(true);

    emit updateSelectedItem(this->currentModel->getModel());
}
