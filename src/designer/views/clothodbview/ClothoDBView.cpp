#include "ClothoDBView.h"
#include "ui_ClothoDBView.h"


ClothoDBView::ClothoDBView(DesignerMainWnd *mainWnd, DesignerModelComponent *model) :
    DesignerViewComponent(mainWnd, model),
    ui(new Ui::ClothoDBView)
{
    ui->setupUi(this);
    this->initiate();    
}

ClothoDBView::~ClothoDBView()
{
    delete ui;
}

void ClothoDBView::initiate()
{
    QFile *file=new QFile(QDesktopServices::storageLocation(QDesktopServices::HomeLocation)+"/AppData/Roaming/.clotho/dev/config/data/private/org.clothocad.connection.configurableconnection/hibernate.cfg.xml");
    if (!file->open(QIODevice::ReadOnly))
    {
        QMessageBox mb;
        mb.setText("Cannot detect your clotho db connection,please configure the connection manually");
        mb.exec();
    }
    if (this->doc.setContent(file))
    {
        QDomElement docElem = doc.documentElement();
        QDomNodeList config=docElem.elementsByTagName("property");

        QString server=config.item(2).toElement().text();
        int t=server.indexOf(":",15);
        server=server.mid(13,t-13);
        QString user=config.item(3).toElement().text();
        QString passwd=config.item(4).toElement().text();
        QString dbname=config.item(5).toElement().text();
        ui->lineEdit_server->setText(server);
        ui->lineEdit_user->setText(user);
        ui->lineEdit_password->setText(passwd);
        ui->lineEdit_dbname->setText(dbname);
    }

    else if(!this->doc.setContent(file))
    {
        QMessageBox mb;
        mb.setText("Cannot detect your clotho db connection,please configure the connection manually");
        mb.exec();       
    }
    file->close();
}

void ClothoDBView::connect()
{

    this->db=QSqlDatabase::addDatabase("QODBC");
    db.setHostName(ui->lineEdit_server->text());
    db.setDatabaseName(ui->lineEdit_dbname->text());
    db.setUserName(ui->lineEdit_user->text());
    db.setPassword(ui->lineEdit_password->text());
    bool ok = db.open();
    if(!ok)
    {
        QMessageBox mb;
        mb.setText("Cannot connect to your db,please reconfigure it!");
        mb.exec();
    }
}

void ClothoDBView::on_pushButton_clicked()
{
    this->connect();
    QSqlQuery query;
    if(query.exec("show tables"))
    {
        QStandardItemModel *tablesModel = new QStandardItemModel(0, 0,this);
        ui->treeView->setModel(tablesModel);

        while(query.next())
        {
            QStandardItem *table = new QStandardItem(query.value(0).toString());
            tablesModel->appendRow(table);
        }
        tablesModel->setHeaderData(0, Qt::Horizontal, ui->lineEdit_dbname->text());
    }
}

void ClothoDBView::on_treeView_doubleClicked(QModelIndex index)
{
    QString tmp=ui->treeView->model()->itemData(index).take(0).toString();
    QSqlQuery query;
    if(query.exec("select * from "+tmp))
    {
        QSqlTableModel *model=new QSqlTableModel(this,this->db);
        model->setTable(tmp);
        model->select();
        int i=0;
        query.next();
        while(!query.value(i).isNull())
        {
            model->setHeaderData(0, Qt::Horizontal,query.value(i).toString());
            i++;
        }
        ui->tableView->setModel(model);
    }

}
