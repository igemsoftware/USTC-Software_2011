#include "AssemblyDBEditor.h"
#include "ui_AssemblyDBEditor.h"
#include "AssemblyLib.h"
#include "DesignerDebug.h"

AssemblyDBEditor::AssemblyDBEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AssemblyDBEditor)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("igame");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("lovewin");
    qDebug() << db.open();

    ui->addSet->setIcon( QIcon(":/designer/common/button/add.ico") );
    ui->removeSet->setIcon( QIcon(":/designer/common/button/remove.ico") );
    connect( ui->addSet , SIGNAL(clicked()) , this , SLOT(addSet()) );
    connect( ui->removeSet , SIGNAL(clicked()) , this , SLOT(removeSet()) );

    agentModel = new QSqlTableModel(this,db);
    agentModel->setTable("agent");
    ui->agentView->setModel(agentModel);

    ruleModel = new QSqlTableModel(this,db);
    ruleModel->setTable("rule");
    ui->ruleView->setModel(ruleModel);

    refresh();
}

AssemblyDBEditor::~AssemblyDBEditor()
{
    db.close();
    delete ui;
}

void AssemblyDBEditor::refresh()
{
    QString current = ui->listWidget->currentItem()?ui->listWidget->currentItem()->text():"";

    QSqlQuery query(db);
    query.exec("SELECT DISTINCT compartment FROM agent");
    ui->listWidget->clear();
    while( query.next() )
    {
        ui->listWidget->addItem(query.value(0).toString());
    }

    if( !current.isEmpty() ) ui->listWidget->setCurrentItem( ui->listWidget->findItems(current));
}

void AssemblyDBEditor::addSet()
{
    QListWidgetItem * item = new QListWidgetItem("new");
    ui->listWidget->addItem( item );
    ui->listWidget->editItem(item);
}

void AssemblyDBEditor::removeSet()
{
    if( QMessageBox::Yes == QMessageBox::question(this,tr("Are you Sure?"),tr("All agents and rules of compartment [%1] will be deleted.\nThis operation can not be undone!\nDo not press Yes unless you know what you are doing!\n").arg(ui->listWidget->currentItem()->text()),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) )
    {
        QSqlQuery query(db);
        query.exec( tr("DELETE FROM agent WHERE compartment='%1'").arg(ui->listWidget->currentItem()->text()));
        refresh();
    }
}
