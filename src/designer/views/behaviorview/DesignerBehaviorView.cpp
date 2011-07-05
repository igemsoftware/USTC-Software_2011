#include "DesignerBehaviorView.h"
#include "ui_DesignerBehaviorView.h"
#include <QtGui>

BehaviorView::BehaviorView(QWidget *parent) :
    DesignerViewItf(parent),
    ui(new Ui::BehaviorView)
{
    ui->setupUi(this);
    this->defined=false;
    this->initiated=false;
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
        this->initiated=true;
        }
    catch(...){
      QMessageBox mb;
      mb.setText("Invalid value");
      mb.exec();
    }
}

void BehaviorView::on_pushButton_2_clicked()
{

  //initiate tabwidget
  if(!this->defined&&this->initiated)
  try
  {
      double timeDuration=ui->lineEdit_timeDuration->text().toDouble();
      double timeInterval=ui->lineEdit_timeInterval->text().toDouble();
      int confTableRowCount=timeDuration/timeInterval+1;
      int confTableColumnCount=ui->lineEdit_maxNode->text().toInt();

      //initiate tableWidget_bahavior
      ui->tableWidget_behavior->setRowCount(confTableRowCount);
      ui->tableWidget_behavior->setColumnCount(confTableColumnCount + 1);
      ui->tableWidget_behavior->setHorizontalHeaderItem(0, new QTableWidgetItem(QString(tr("Time(s)"))));

      for(int i = 0; i < confTableColumnCount; i++)
      {
          ui->tableWidget_behavior->setHorizontalHeaderItem(i + 1, new QTableWidgetItem(ui->tableWidget_define->item(i,0)->text()));
          ui->tableWidget_behavior->setItem(0,i+1,new QTableWidgetItem(QString::number(0)));
          ui->comboBox->addItem(ui->tableWidget_define->item(i,0)->text());
      }
      for(int i=0;i<confTableRowCount;i++){
          ui->tableWidget_behavior->setItem(i,0,new QTableWidgetItem(QString::number(i*timeInterval)));
      }
      ui->tableWidget_behavior->setCurrentCell(0, 0);
      ui->tableWidget_behavior->setSelectionMode(QTableView::ContiguousSelection);
      ui->comboBox->addItem(tr("all"));

      //mark defined
      this->defined=true;
      this->prepareToPlot();     
  }
  catch(...)
  {
    QMessageBox mb;
    mb.setText("Invalid value");
    mb.exec();
  }
  ui->tabWidget->setCurrentIndex(2);
}

void BehaviorView::on_pushButton_ViewGraphic_clicked()
{
    ui->PlotWidget->drawable=false;
    ui->tabWidget_2->setCurrentIndex(1);
    ui->PlotWidget->PlotFromValue();
    if(ui->comboBox->itemText(ui->comboBox->count()-1)!="all")
    {
        ui->comboBox->addItem(tr("all"));
    }
    ui->comboBox->setCurrentIndex(ui->comboBox->count()-1);
}
void BehaviorView::on_pushButton_Draw_clicked()
{
    if(this->defined)
    {
        if(!ui->PlotWidget->drawable)
        {
            if(ui->comboBox->itemText(ui->comboBox->count()-1)=="all")
            {
                ui->comboBox->removeItem(ui->comboBox->count()-1);
            }
            ui->comboBox->setCurrentIndex(0);
            ui->pushButton_Draw->setDown(true);
        }
        if(ui->PlotWidget->drawable)
        {
            ui->comboBox->addItem("all");
            ui->comboBox->setCurrentIndex(0);
            ui->pushButton_Draw->setDown(false);
        }
        ui->PlotWidget->drawable=!ui->PlotWidget->drawable;
        ui->PlotWidget->clearImage();
    }
}

void BehaviorView::on_pushButton_Clear_clicked()
{
    ui->PlotWidget->clearImage();
}

void BehaviorView::on_comboBox_currentIndexChanged()
{
    if(this->defined)
    {
        if(ui->PlotWidget->drawable)
        {
            QComboBox *comboBox=(QComboBox *)(ui->tableWidget_define->cellWidget(ui->comboBox->currentIndex(),1));
            ui->PlotWidget->myPenColor=comboBox->itemData(comboBox->currentIndex(), Qt::UserRole).value<QColor>();
            ui->PlotWidget->vc->clear();
        }
        else
            ui->PlotWidget->PlotFromValue();
    }
}

void BehaviorView::on_pushButton_ViewValue_clicked()
{
    for(int i=0;i<ui->PlotWidget->x;i++)
    {
        ui->tableWidget_behavior->item(i,0)->setText(QString::number(i*ui->lineEdit_timeInterval->text().toDouble()));
    }
    ui->tabWidget_2->setCurrentIndex(0);
    if(ui->comboBox->itemText(ui->comboBox->currentIndex())!="all")
    {
        for(int i=0;i<ui->PlotWidget->vc->count();i++)
        {
            int j=int((ui->PlotWidget->vc->value(i).x()-30)*ui->PlotWidget->maxx/(ui->PlotWidget->size().width()-40));
            ui->tableWidget_behavior->setItem(j+1,1+ui->comboBox->currentIndex(),new QTableWidgetItem
            (QString::number(ui->PlotWidget->maxy-(ui->PlotWidget->vc->value(i).y()-10)*ui->PlotWidget->maxy/(ui->PlotWidget->size().height()-20))));
        }
    }
}

void BehaviorView::prepareToPlot()
{
    double timeDuration=ui->lineEdit_timeDuration->text().toDouble();
    double timeInterval=ui->lineEdit_timeInterval->text().toDouble();
    int confTableRowCount=timeDuration/timeInterval+1;

    //deliver parameters to PlotWidget
    ui->PlotWidget->node=ui->lineEdit_maxNode->text().toInt();    
    ui->PlotWidget->x=confTableRowCount;
    ui->PlotWidget->deltax=timeInterval;
    ui->PlotWidget->maxy=ui->lineEdit_maxConcentration->text().toDouble();
    ui->PlotWidget->maxx=ui->lineEdit_timeDuration->text().toDouble();
    ui->PlotWidget->cb=ui->comboBox;
    ui->PlotWidget->tab_1=ui->tableWidget_define;
    ui->PlotWidget->tab_2=ui->tableWidget_behavior;
}
