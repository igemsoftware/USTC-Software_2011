#include "NetworkViewSubstanceEditor.h"
#include "ui_NetworkViewSubstanceEditor.h"
#include <QMessageBox>

NetworkViewSubstanceEditor::NetworkViewSubstanceEditor(QScriptValue &value, QSet<QString> *idSpace, QWidget *parent):
    QDialog(parent),
    ui(new Ui::NetworkViewSubstanceEditor)
{
    ui->setupUi(this);
    this->property=value;
    this->idSpace=idSpace;
    ui->ID_edit->setText(value.property("id").toString());
    ui->Metaid_eidt->setText(value.property("metaid").toString());
    ui->Name_edit->setText(value.property("name").toString());
    ui->SBO_term->setText(value.property("sboTerm").toString());
    ui->Units_eidt->setText(value.property("substanceUnits").toString());
    ui->initialC_edit->setText(value.property("initialConcentration").toString());
}

NetworkViewSubstanceEditor::~NetworkViewSubstanceEditor()
{
    delete ui;
}

void NetworkViewSubstanceEditor::accept()
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
    property.setProperty("initialConcentration",ui->initialC_edit->text());
    property.setProperty("substanceUnits",ui->Units_eidt->text());
    property.setProperty("metaid",ui->Metaid_eidt->text());
    property.setProperty("sboTerm",ui->SBO_term->text());
    QDialog::accept();
}
