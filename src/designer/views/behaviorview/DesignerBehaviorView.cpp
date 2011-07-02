#include "DesignerBehaviorView.h"
#include "ui_DesignerBehaviorView.h"
#include <QtGui>

BehaviorView::BehaviorView(QWidget *parent) :
    DesignerViewItf(parent),
    ui(new Ui::BehaviorView)
{
    ui->setupUi(this);
    this->defined=false;
}

BehaviorView::~BehaviorView()
{
    delete ui;
}

void BehaviorView::on_pushButton_clicked()
{
    this->defined=false;
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
            cb->addItem(QObject::tr("Red"), Qt::red);
            cb->addItem(QObject::tr("blue"), Qt::blue);
            cb->addItem(QObject::tr("black"), Qt::black);
            cb->addItem(QObject::tr("gray"), Qt::gray);
            cb->addItem(QObject::tr("green"), Qt::green);
            cb->addItem(QObject::tr("yellow"), Qt::yellow);
            ui->tableWidget_define->setCellWidget(i,1,cb);
        }
        ui->tableWidget_define->setHorizontalHeaderItem(0,new QTableWidgetItem("name"));
        ui->tableWidget_define->setHorizontalHeaderItem(1,new QTableWidgetItem("color"));
        ui->tableWidget_define->setCurrentCell(0, 0);
        ui->tableWidget_define->setSelectionMode(QTableView::ContiguousSelection);
        ui->comboBox->clear();
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
  if(!this->defined)try
  {
      double timeDuration=ui->lineEdit_timeDuration->text().toDouble();
      double timeInterval=ui->lineEdit_timeInterval->text().toDouble();
      int confTableRowCount=timeDuration/timeInterval+1;
      int confTableColumnCount=ui->lineEdit_maxNode->text().toInt();
      //initiate tableWidget_bahavior
      ui->tableWidget_behavior->setRowCount(confTableRowCount);
      ui->tableWidget_behavior->setColumnCount(confTableColumnCount + 1);
      ui->tableWidget_behavior->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Time(s)")));
      for(int i = 0; i < confTableColumnCount; i++)
      {
          ui->tableWidget_behavior->setHorizontalHeaderItem(i + 1, new QTableWidgetItem(ui->tableWidget_define->item(i,0)->text()));
          ui->comboBox->addItem(ui->tableWidget_define->item(i,0)->text());
      }
      for(int i=0;i<confTableRowCount;i++){
          ui->tableWidget_behavior->setItem(i,0,new QTableWidgetItem(QString(QString::number(i*timeInterval))));
      }
      ui->tableWidget_behavior->setCurrentCell(0, 0);
      ui->tableWidget_behavior->setSelectionMode(QTableView::ContiguousSelection);
      //initiate combobox
      ui->comboBox->addItem("all");
      //mark defined
      this->defined=true;
      //deliver parameters to PlotWidget
      ui->PlotWidget->x=confTableRowCount;
      ui->PlotWidget->deltax=timeInterval;
      ui->PlotWidget->maxy=ui->lineEdit_maxConcentration->text().toDouble();
  }
  catch(...){
    QMessageBox mb;
    mb.setText("Invalid value");
    mb.exec();
}
}

void BehaviorView::on_pushButton_ViewGraphic_clicked()
{
    ui->tabWidget_2->setCurrentIndex(1);
}

void BehaviorView::on_pushButton_Draw_clicked()
{
    ui->comboBox->setCurrentIndex(0);
    if(!ui->PlotWidget->drawable)ui->comboBox->removeItem(ui->comboBox->count()-1);
    ui->PlotWidget->drawable=true;
}

void BehaviorView::on_pushButton_Clear_clicked()
{
    ui->PlotWidget->clearImage();
}

void BehaviorView::on_comboBox_currentIndexChanged()
{
    if(ui->PlotWidget->drawable)
    {
        QComboBox *comboBox=(QComboBox *)(ui->tableWidget_define->cellWidget(ui->comboBox->currentIndex(),1));
        ui->PlotWidget->myPenColor=comboBox->itemData(comboBox->currentIndex(), Qt::UserRole).value<QColor>();
    }
}

void BehaviorView::on_pushButton_ViewValue_clicked()
{
    ui->tabWidget_2->setCurrentIndex(0);
    ui->PlotWidget->drawable=false;
}
