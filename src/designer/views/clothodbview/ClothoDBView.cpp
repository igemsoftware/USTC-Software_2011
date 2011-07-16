#include "ClothoDBView.h"
#include "ui_ClothoDBView.h"
#include <QXmlDefaultHandler>

ClothoDBView::ClothoDBView(QWidget *parent) :
    QWidget(parent),
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
    QFile *file=new QFile(QDesktopServices::HomeLocation+"AppData/Roaming/.clotho/dev/config/data/private/org.clothocad.connection.configurableconnection/hibernate.cfg.xml");
    this->source=new QXmlInputSource(file);
    QXmlDefaultHandler *handler = new QXmlDefaultHandler;
    this->xmlReader.setContentHandler(handler);
    this->xmlReader.setErrorHandler(handler);
    bool ok = xmlReader.parse(source);
    if (!ok)
    {
        QMessageBox mb;
        mb.setText("Cannot detect your clotho db connection,please configure the connection manually");
        mb.exec();
    }
    else
    {
//        ui->lineEdit_server->setText(QString::QString(this->xmlReader.property("hibernate.connection.url")));
//        ui->lineEdit_user->setText(QString::QString(this->xmlReader.property("hibernate.connection.username")));
//        ui->lineEdit_password->setText(QString::QString(this->xmlReader.property("hibernate.connection.password")));
    }

}

void ClothoDBView::connect()
{



}
