#include "AssemblyDBEditor.h"
#include "ui_AssemblyDBEditor.h"
#include "AssemblyLib.h"
#include "DesignerDebug.h"
#include <QSqlRecord>

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

    ui->addAgent->setIcon( QIcon(":/designer/common/button/add.ico") );
    ui->removeAgent->setIcon( QIcon(":/designer/common/button/remove.ico") );
    connect( ui->addAgent , SIGNAL(clicked()) , this , SLOT(addAgent()) );
    connect( ui->removeAgent , SIGNAL(clicked()) , this , SLOT(removeAgent()) );

    ui->addRule->setIcon( QIcon(":/designer/common/button/add.ico") );
    ui->removeRule->setIcon( QIcon(":/designer/common/button/remove.ico") );
    connect( ui->addRule , SIGNAL(clicked()) , this , SLOT(addRule()) );
    connect( ui->removeRule , SIGNAL(clicked()) , this , SLOT(removeRule()) );

    ui->saveAgent->setIcon( QIcon(":/designer/common/button/save.ico") );
    ui->saveRule->setIcon( QIcon(":/designer/common/button/save.ico") );

    agentModel = new QSqlTableModel(this,db);
    ruleModel = new QSqlTableModel(this,db);

    connect( ui->listWidget , SIGNAL(currentTextChanged(QString)) , this , SLOT(selectCompartment(QString)) );

    refresh();
}

AssemblyDBEditor::~AssemblyDBEditor()
{
    db.close();
    delete ui;
}

void AssemblyDBEditor::selectCompartment(QString compartment)
{
    QList<QListWidgetItem*> list = ui->listWidget->findItems(compartment,Qt::MatchExactly);
    if( list.isEmpty() ) return;
    ui->listWidget->setCurrentItem( list.first() );

    agentModel->deleteLater();
    ruleModel->deleteLater();
    agentModel = new QSqlTableModel(this,db);
    ruleModel = new QSqlTableModel(this,db);
    connect( ui->saveAgent , SIGNAL(clicked()) , agentModel , SLOT(submitAll()) );
    connect( ui->saveRule , SIGNAL(clicked()) , ruleModel , SLOT(submitAll()) );
    agentModel->setEditStrategy( QSqlTableModel::OnManualSubmit );
    ruleModel->setEditStrategy( QSqlTableModel::OnManualSubmit );
    //ui->ruleView->selectionModel()->deleteLater();
    //ui->agentView->selectionModel()->deleteLater();
    agentModel->setTable( tr("%1_agent").arg(compartment) );
    ruleModel->setTable( tr("%1_rule").arg(compartment) );
    agentModel->select();
    ruleModel->select();
    ui->ruleView->setModel(ruleModel);
    ui->agentView->setModel(agentModel);
    //ui->ruleView->hideColumn(0);
}

void AssemblyDBEditor::refresh()
{
    QString current = ui->listWidget->currentItem()?ui->listWidget->currentItem()->text():"";

    QSqlQuery query(db);
    query.exec("SELECT id FROM compartment");
    ui->listWidget->clear();
    while( query.next() )
    {
        ui->listWidget->addItem(query.value(0).toString());
    }
    if( !current.isEmpty() )
    {
        selectCompartment(current);
    }
}

void AssemblyDBEditor::addSet()
{
    QDialog dialog;
    QVBoxLayout * vlayout = new QVBoxLayout;
    QHBoxLayout * hlayout = new QHBoxLayout;
    QLineEdit * text = new QLineEdit;
    QPushButton * ok = new QPushButton("Ok");
    QPushButton * cancel = new QPushButton("Cancel");
    connect( ok , SIGNAL(clicked()) , &dialog , SLOT(accept()) );
    connect( cancel , SIGNAL(clicked()) , &dialog , SLOT(reject()) );
    vlayout->addWidget( text );
    hlayout->addWidget(ok);
    hlayout->addWidget(cancel);
    vlayout->addLayout(hlayout);
    dialog.setLayout(vlayout);
    dialog.setWindowTitle("Enter RuleSet Name");

    if( dialog.exec() == QDialog::Accepted )
    {
        if( text->text().isEmpty() )
        {
            QMessageBox::information( this , "Error" , "Empty RuleSet Name!" );
            return;
        }
        QSqlQuery query(db);
        query.exec( tr("SELECT COUNT(id) FROM compartment WHERE id = \'%1\'").arg(text->text()) );
        query.next();
        if( query.value(0).toInt() )
        {
            QMessageBox::information( this , "Error" , tr("RuleSet %1 already exists!").arg(text->text()) );
            return;
        }
        QRegExp rx("^([a-zA-Z])(\\w{0,254})$");
        if( rx.indexIn(text->text()) > -1 )
        {
            query.exec( tr("INSERT INTO compartment (id) VALUE(\'%1\')").arg(text->text()));
            query.exec( tr("CREATE TABLE %1_agent( "
                           "type ENUM('prom','rbs','pcs','term','mol') NULL,"
                           "id  CHAR(20) NOT NULL,"
                           "rate   VARCHAR(255) NULL,"
                           "defautl_site CHAR(255) NULL,"
                           "primary key(id) )" ).arg(text->text()) );
            query.exec( tr("CREATE TABLE %1_rule( "
                           "id INT UNSIGNED NOT NULL AUTO_INCREMENT,"
                           "lhs VARCHAR(255) NULL,"
                           "rhs VARCHAR(255) NULL,"
                           "reversible ENUM('Y','N') NULL default 'Y',"
                           "rate_on  VARCHAR(255) NOT NULL,"
                           "rate_off VARCHAR(255) NOT NULL,"
                           "PRIMARY KEY (id) )" ).arg(text->text()) );
            refresh();
        }
    }

}

void AssemblyDBEditor::removeSet()
{
    if( QMessageBox::Yes == QMessageBox::question(this,tr("Are you Sure?"),tr("All agents and rules of compartment [%1] will be deleted.\nThis operation can not be undone!\nDo not press Yes unless you know what you are doing!\n").arg(ui->listWidget->currentItem()->text()),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) )
    {
        QSqlQuery query(db);
        query.exec( tr("DELETE FROM compartment WHERE id='%1'").arg(ui->listWidget->currentItem()->text()));
        query.exec( tr("DROP TABLE %1_agent").arg(ui->listWidget->currentItem()->text()) );
        query.exec( tr("DROP TABLE %1_rule").arg(ui->listWidget->currentItem()->text()) );
        refresh();
    }
}

void AssemblyDBEditor::addRule()
{
    ruleModel->insertRows(0,1);
}

void AssemblyDBEditor::removeRule()
{
}

void AssemblyDBEditor::addAgent()
{
    agentModel->insertRows(0,1);
}

void AssemblyDBEditor::removeAgent()
{

}
