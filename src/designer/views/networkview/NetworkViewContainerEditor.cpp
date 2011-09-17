#include "NetworkViewContainerEditor.h"
#include "ui_NetworkViewContainerEditor.h"
#include <QMessageBox>

NetworkViewContainerEditor::NetworkViewContainerEditor(QScriptValue &value, QSet<QString> *idSpace, QWidget *parent):
    QDialog(parent),
    ui(new Ui::NetworkViewContainerEditor)
{
    ui->setupUi(this);
    this->property=value;
    this->idSpace=idSpace;
    ui->ID_edit->setText(value.property("id").toString());
    ui->Metaid_eidt->setText(value.property("metaid").toString());
    ui->Name_edit->setText(value.property("name").toString());
    ui->SBO_term->setText(value.property("sboTerm").toString());
    ui->Size_edit->setText(value.property("size").toString());
    ui->Units_eidt->setText(value.property("units").toString());
}

NetworkViewContainerEditor::~NetworkViewContainerEditor()
{
    delete ui;
}

void NetworkViewContainerEditor::accept()
{
    if(this->idSpace->contains(ui->ID_edit->text()) && property.property("id").toString()!=ui->ID_edit->text())
    {
        QMessageBox *qmb=new QMessageBox();
        qmb->setText("ID already exit,please change to another one!");
        qmb->exec();
        return;
    }
    idSpace->remove(property.property("id").toString());
    idSpace->insert(ui->ID_edit->text());
    property.setProperty("id",ui->ID_edit->text());
    property.setProperty("name",ui->Name_edit->text());
    property.setProperty("units",ui->Units_eidt->text());
    property.setProperty("size",ui->Size_edit->text());
    property.setProperty("metaid",ui->Metaid_eidt->text());
    property.setProperty("sboTerm",ui->SBO_term->text());
    QDialog::accept();
}
