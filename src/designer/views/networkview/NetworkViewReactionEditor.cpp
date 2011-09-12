#include "NetworkViewReactionEditor.h"
#include "ui_NetworkViewReactionEditor.h"
#include <QMessageBox>
#include <QXmlQuery>

NetworkViewReactionEditor::NetworkViewReactionEditor(QScriptValue &value, QSet<QString> *idSpace, QWidget *parent):
    QDialog(parent),
    ui(new Ui::NetworkViewReactionEditor)
{
    this->property=value;
    this->idSpace=idSpace;
    QXmlQuery query(QXmlQuery::XSLT20);
    QString *out=new QString();
    query.setFocus(value.property("kineticLaw").property("math").toString());
    query.setQuery(QUrl("../src/designer/views/networkview/mmlctop2_0.xsl"));
    query.evaluateTo(out);

    ui->setupUi(this);
//    ui->widget->setContent("      <math xmlns=/"http://www.w3.org/1998/Math/MathML/">        <mrow>          <mi>x</mi>          <mo>=</mo>          <mfrac>            <mrow>              <mo form=/"prefix/">&#x2212;<!-- &minus; --></mo>              <mi>b</mi>              <mo>&#x00B1;<!-- &PlusMinus; --></mo>              <msqrt>                <msup>                  <mi>b</mi>                  <mn>2</mn>                </msup>                <mo>&#x2212;<!-- &minus; --></mo>                <mn>4</mn>                <mo>&#x2062;<!-- &InvisibleTimes; --></mo>                <mi>a</mi>                <mo>&#x2062;<!-- &InvisibleTimes; --></mo>                <mi>c</mi>              </msqrt>            </mrow>            <mrow>              <mn>2</mn>              <mo>&#x2062;<!-- &InvisibleTimes; --></mo>              <mi>a</mi>            </mrow>          </mfrac>        </mrow>      </math>");
//    ui->widget->setContent(*out);
    ui->ID_edit->setText(value.property("id").toString());
    ui->Metaid_eidt->setText(value.property("metaid").toString());
    ui->Name_edit->setText(value.property("name").toString());
    ui->SBO_term->setText(value.property("sboTerm").toString());

    if(value.property("revsersible").toString()=="true")
        ui->reversible->setChecked(true);
    else
        ui->reversible->setChecked(false);
    if(value.property("fast").toString()=="true")
        ui->fast->setChecked(true);
    else
        ui->fast->setChecked(false);
}

NetworkViewReactionEditor::~NetworkViewReactionEditor()
{
    delete ui;
}

void NetworkViewReactionEditor::accept()
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
    if(ui->reversible->isChecked())
        property.setProperty("reversible","true");
    else
        property.setProperty("reversible","false");
    if(ui->fast->isChecked())
        property.setProperty("fast","true");
    else
        property.setProperty("fast","false");
    property.setProperty("metaid",ui->Metaid_eidt->text());
    property.setProperty("sboTerm",ui->SBO_term->text());
    QDialog::accept();
}

