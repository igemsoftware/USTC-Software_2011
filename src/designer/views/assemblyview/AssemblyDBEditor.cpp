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

    builtinTables.append("agent");
    builtinTables.append("inducer");
    builtinTables.append("function");
    builtinTables.append("medium");

    db = QSqlDatabase::database("igame");

    ui->addSet->setIcon( QIcon(":/designer/common/button/add.ico") );
    ui->removeSet->setIcon( QIcon(":/designer/common/button/remove.ico") );
    connect( ui->addSet , SIGNAL(clicked()) , this , SLOT(addSet()) );
    connect( ui->removeSet , SIGNAL(clicked()) , this , SLOT(removeSet()) );

    ui->addRow->setIcon( QIcon(":/designer/common/button/add.ico") );
    ui->removeRow->setIcon( QIcon(":/designer/common/button/remove.ico") );
    connect( ui->addRow , SIGNAL(clicked()) , this , SLOT(addRow()) );
    connect( ui->removeRow , SIGNAL(clicked()) , this , SLOT(removeRow()) );

    ui->saveTable->setIcon( QIcon(":/designer/common/button/save.ico") );

    tableModel = new QSqlTableModel(this,db);

    connect( ui->listWidget , SIGNAL(currentTextChanged(QString)) , this , SLOT(selectTable(QString)) );

    refresh();
}

AssemblyDBEditor::~AssemblyDBEditor()
{
    delete ui;
}

void AssemblyDBEditor::selectTable(QString table)
{
    QList<QListWidgetItem*> list = ui->listWidget->findItems(table,Qt::MatchExactly);
    if( list.isEmpty() ) return;
    ui->listWidget->setCurrentItem( list.first() );

    tableModel->deleteLater();
    tableModel = new QSqlTableModel(this,db);
    connect( ui->saveTable , SIGNAL(clicked()) , tableModel , SLOT(submitAll()) );
    tableModel->setEditStrategy( QSqlTableModel::OnManualSubmit );
    tableModel->setTable(table);
    tableModel->select();
    ui->tableView->setModel(tableModel);
}

void AssemblyDBEditor::refresh()
{
    QString current = ui->listWidget->currentItem()?ui->listWidget->currentItem()->text():"";

    QSqlQuery query(db);
    query.exec("SHOW TABLES");
    ui->listWidget->clear();
    ui->listWidget->addItems(builtinTables);
    while( query.next() )
    {
        if( builtinTables.contains(query.value(0).toString())) continue;
        ui->listWidget->addItem(query.value(0).toString());
    }
    if( !current.isEmpty() )
    {
        selectTable(current);
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
        query.exec( QString("SHOW TABLES LIKE \'%1\'").arg(text->text()) );
        if( query.numRowsAffected() )
        {
            QMessageBox::information( this , "Error" , tr("RuleSet %1 already exists!").arg(text->text()) );
            return;
        }
        QRegExp rx("^([a-zA-Z])(\\w{0,254})$");
        if( rx.indexIn(text->text()) > -1 )
        {
            query.exec( QString("CREATE TABLE %1"
                        "("
                            "name VARCHAR(255) NOT NULL,"
                            "reactant_patterns VARCHAR(255) NULL,"
                            "product_patterns VARCHAR(255) NULL,"
                            "is_reversible ENUM(\'True\',\'False\') NULL default \'False\',"
                            "forward_rate_law  VARCHAR(255) NOT NULL,"
                            "reverse_rate_law  VARCHAR(255) NULL,"
                            "PRIMARY KEY (name)"
                        ");").arg(text->text())
                        );
            refresh();
        }else{
            QMessageBox::information( this , "Error" , tr("\"%1\" is not a valid rule-set name!").arg(text->text()) );
            return;
        }
    }

}

void AssemblyDBEditor::removeSet()
{
    if( ui->listWidget->currentItem() == 0 ) return;
    if( QMessageBox::Yes == QMessageBox::question(this,tr("Are you Sure?"),tr("All agents and rules of compartment [%1] will be deleted.\nThis operation can not be undone!\nDo not press Yes unless you know what you are doing!\n").arg(ui->listWidget->currentItem()->text()),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) )
    {
        QSqlQuery query(db);
        query.exec( tr("DROP TABLE %1").arg(ui->listWidget->currentItem()->text()) );
        refresh();
    }
}

void AssemblyDBEditor::addRow()
{
    tableModel->insertRows(0,1);
}

void AssemblyDBEditor::removeRow()
{
    tableModel->removeRows( ui->tableView->currentIndex().row() , 1 );
}

