#include "DesignerBehaviorView.h"
#include "ui_DesignerBehaviorView.h"
#include <QtGui>

BehaviorView::BehaviorView(QWidget *parent) :
    DesignerViewItf(parent),
    ui(new Ui::BehaviorView)
{
    ui->setupUi(this);

    connect( ui->pushButton , SIGNAL(clicked()) , this , SLOT(on_pushButton_clicked()) );
    connect( ui->pushButton_2 , SIGNAL(clicked()) , this , SLOT(on_pushButton_2_clicked()) );
}

BehaviorView::~BehaviorView()
{
    delete ui;
}

void BehaviorView::on_pushButton_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
    try
    {
        int confTableRowCount=ui->lineEdit_maxNode->text().toInt();
        int confTableColumnCount=2;
        ui->tableWidget_define->setRowCount(confTableRowCount);
        ui->tableWidget_define->setColumnCount(confTableColumnCount);

        for(int i = 0; i < confTableRowCount; i++)
        {
            ui->tableWidget_define->setItem(i,0,new QTableWidgetItem(tr("node")+QString::number(i+1)));
            QComboBox *cb=new QComboBox(ui->tableWidget_define);
            cb->addItem("Qt::red");
            cb->addItem("Qt::yellow");
            cb->addItem("Qt::black");
            cb->addItem("Qt::green");
            cb->addItem("Qt::gray");
            cb->addItem("Qt::blue");
            ui->tableWidget_define->setCellWidget(i,1,cb);
        }
        ui->tableWidget_define->setHorizontalHeaderItem(0,new QTableWidgetItem("name"));
        ui->tableWidget_define->setHorizontalHeaderItem(1,new QTableWidgetItem("color"));
        ui->tableWidget_define->setCurrentCell(0, 0);
        ui->tableWidget_define->setSelectionMode(QTableView::ContiguousSelection);
    }
    catch(...){
      QMessageBox mb;
      mb.setText("Invalid value");
      mb.exec();
    }
}

void BehaviorView::on_pushButton_2_clicked()
{
  ui->tabWidget->setCurrentIndex(2);
  //initiate tabwidget
  try
  {
      double timeDuration=ui->lineEdit_timeDuration->text().toDouble();
      double timeInterval=ui->lineEdit_timeInterval->text().toDouble();
      int confTableRowCount=timeDuration/timeInterval+1;
      int confTableColumnCount=ui->lineEdit_maxNode->text().toInt();
      ui->tableWidget_behavior->setRowCount(confTableRowCount);
      ui->tableWidget_behavior->setColumnCount(confTableColumnCount + 1);
      ui->tableWidget_behavior->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Time(s)")));
      for(int i = 0; i < confTableColumnCount; i++)
      {
          ui->tableWidget_behavior->setHorizontalHeaderItem(i + 1, new QTableWidgetItem(ui->tableWidget_define->item(i,0)->text()));
      }
      for(int i=0;i<confTableRowCount;i++){
          ui->tableWidget_behavior->setItem(i,0,new QTableWidgetItem(QString(QString::number(i*timeInterval))));
      }
      ui->tableWidget_behavior->setCurrentCell(0, 0);
      ui->tableWidget_behavior->setSelectionMode(QTableView::ContiguousSelection);
  }
  catch(...){
    QMessageBox mb;
    mb.setText("Invalid value");
    mb.exec();
}
}
