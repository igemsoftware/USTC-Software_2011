#include <QtGui>
#include <QtCore>
#include "BehaviorView.h"
#include "ui_BehaviorView.h"

#include "common/drawwnd/DesignerDrawWnd.h"

BehaviorView::BehaviorView(DesignerMainWnd *mainWnd, DesignerModelComponent *model) :
    DesignerViewComponent(mainWnd, model),
    ui(new Ui::BehaviorView)
{
    ui->setupUi(this);
    this->nodes=0;
    this->times=0;
    this->timeNumLimit=10000;
    this->maxt=ui->TimeEdit->text().toDouble();
    this->maxc=ui->ConcentrationEdit->text().toDouble();
    this->initiated=false;
    this->initiate();
    ui->PlotWidget->installEventFilter(this);

//    DesignerDrawWnd window;
//    window.exec();
}

BehaviorView::~BehaviorView()
{
    delete ui;
}
bool BehaviorView::eventFilter(QObject *obj, QEvent *event)
{
    if(ui->PlotWidget->drawable && obj==ui->PlotWidget && (event->type()==QEvent::MouseMove || event->type()==QEvent::MouseButtonRelease))
    {
        QMouseEvent * me=dynamic_cast<QMouseEvent *>(event);
        if(me->pos().x()<ui->PlotWidget->lastPoint.x())
            return true;
        else
            return false;
    }
    else
        return QWidget::eventFilter(obj,event);
}

void BehaviorView::addnode()
{
    ui->tableWidget_value->setRowCount(this->nodes+2);
    ui->tableWidget_value->setItem(this->nodes+1,0,new QTableWidgetItem(tr("node")+QString::number(this->nodes+1)));
    QComboBox *cb=new QComboBox(ui->tableWidget_value);
    cb->addItem(QObject::tr("Red"), Qt::red);
    cb->addItem(QObject::tr("blue"), Qt::blue);
    cb->addItem(QObject::tr("black"), Qt::black);
    cb->addItem(QObject::tr("gray"), Qt::gray);
    cb->addItem(QObject::tr("green"), Qt::green);
    cb->addItem(QObject::tr("yellow"), Qt::yellow);
    ui->tableWidget_value->setCellWidget(this->nodes+1,1,cb);
    for(int i=2;i<this->times;i++)
    {
        ui->tableWidget_value->setItem(this->nodes,i,new QTableWidgetItem());
    }
    this->nodes++;
}

void BehaviorView::addtime()
{
    ui->tableWidget_value->setColumnCount(this->times+3);
    ui->tableWidget_value->setHorizontalHeaderItem(this->times+2,new QTableWidgetItem("Time "+QString::number(this->times+1)));
    for(int i=0;i<=this->times;i++)
    {
        ui->tableWidget_value->setItem(0,i+2,new QTableWidgetItem(QString::number(i*this->maxt/this->times)));
    }
    for(int i=1;i<this->nodes;i++)
    {
        ui->tableWidget_value->setItem(i,this->times+2,new QTableWidgetItem());
    }
    this->times++;
        ui->TimeStepEdit->setText(QString::number(this->maxt/(this->times-1)));
}

void BehaviorView::initiate()
{
        ui->tableWidget_value->setColumnCount(2);
        ui->tableWidget_value->setRowCount(1);        
        ui->tableWidget_value->setHorizontalHeaderItem(0,new QTableWidgetItem(tr("Name")));
        ui->tableWidget_value->setHorizontalHeaderItem(1,new QTableWidgetItem(tr("Color")));
        ui->tableWidget_value->setSelectionMode(QTableView::ContiguousSelection);
        ui->comboBox->clear();
        this->addnode();
        this->addtime();
        this->addtime();
        ui->tableWidget_value->setCurrentCell(0, 0);
        this->initiated=true;
}

void BehaviorView::on_pushButton_Draw_clicked()
{
    if(this->initiated)
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

void BehaviorView::prepareToPlot()
{
    //deliver parameters to PlotWidget
    ui->PlotWidget->nodes=this->nodes;
    ui->PlotWidget->times=this->times;
    ui->PlotWidget->maxc=this->maxc;
    ui->PlotWidget->maxt=this->maxt;
    ui->PlotWidget->deltat=ui->TimeStepEdit->text().toDouble();
    ui->PlotWidget->draw=ui->pushButton_Draw;
    ui->PlotWidget->cb=ui->comboBox;
    ui->PlotWidget->tab=ui->tableWidget_value;
    ui->PlotWidget->drawable=false;
    //combobox set
    for(int i=0;i<this->nodes;i++)
    {
        ui->comboBox->addItem(ui->tableWidget_value->item(i+1,0)->text());
    }
    ui->comboBox->addItem(tr("all"));
    ui->comboBox->setCurrentIndex(ui->comboBox->count()-1);
}

void BehaviorView::on_comboBox_currentIndexChanged()
{
    if(this->initiated)
    {
        if(ui->PlotWidget->drawable)
        {
            QComboBox *comboBox=(QComboBox *)(ui->tableWidget_value->cellWidget(ui->comboBox->currentIndex()+1,1));
            ui->PlotWidget->myPenColor=comboBox->itemData(comboBox->currentIndex(), Qt::UserRole).value<QColor>();
            ui->PlotWidget->vc->clear();
        }
        else
            ui->PlotWidget->PlotFromValue();
    }
}

void BehaviorView::on_tabWidget_currentChanged(int index)
{
    if(index==1)
    {
        this->initiated=true;
        this->prepareToPlot();
    }
    if(index==0)
    {
        this->initiated=false;
        ui->comboBox->clear();
    }
}

void BehaviorView::on_ConcentrationEdit_editingFinished()
{
    ui->tabWidget->setCurrentIndex(0);
    this->maxc=ui->ConcentrationEdit->text().toDouble();
}

void BehaviorView::on_ResetButton_clicked()
{
    for(int i=0;i<this->nodes;i++)
    {
        for(int j=0;j<this->times;j++)
        {
            ui->tableWidget_value->setItem(i+1,j+2,new QTableWidgetItem());
            ui->tabWidget->setCurrentIndex(0);
        }
    }
}

void BehaviorView::on_pushButton_Clear_clicked()
{
    ui->PlotWidget->clearImage();
}

void BehaviorView::on_generatevalueButton_clicked()
{
    for(int i=0;i<this->times;i++)
    {
        ui->tableWidget_value->setItem(0,i+2,new QTableWidgetItem(QString::number(i*this->maxt/(this->times-1))));
    }
    int j=int((ui->PlotWidget->vc->value(0).x()-30)*this->maxt/((ui->PlotWidget->size().width()-40)*this->maxt/(this->times-1)));
    for(int i=0;i<ui->PlotWidget->vc->count();i++)
    {
        ui->tableWidget_value->setItem(ui->comboBox->currentIndex()+1,j+i+2,new QTableWidgetItem
        (QString::number(this->maxc-(ui->PlotWidget->vc->value(i).y()-10)*this->maxc/(ui->PlotWidget->size().height()-20))));
    }
    ui->PlotWidget->vc->clear();
}

void BehaviorView::on_TimeStepEdit_editingFinished()
{
    int timenum=int(ui->TimeEdit->text().toDouble()/ui->TimeStepEdit->text().toDouble())+1;
    if(timenum<1 || timenum==this->times)
        return;    
    this->times=timenum;
    ui->tableWidget_value->setColumnCount(this->times+2);
    for(int i=0;i<this->times;i++)
    {
        ui->tableWidget_value->setHorizontalHeaderItem(i+2,new QTableWidgetItem("Time "+QString::number(i+1)));
        ui->tableWidget_value->setItem(0,i+2,new QTableWidgetItem(QString::number(i*this->maxt/(this->times-1))));
    }
    this->on_ResetButton_clicked();
}

void BehaviorView::on_TimeStepEdit_textChanged(QString )
{
    int timenum=int(ui->TimeEdit->text().toDouble()/ui->TimeStepEdit->text().toDouble())+1;
    if(timenum>this->timeNumLimit+1)
        ui->TimeStepEdit->setText(QString::number(this->maxt/this->timeNumLimit));
}

void BehaviorView::on_TimeEdit_editingFinished()
{
    ui->tabWidget->setCurrentIndex(0);
    int timenum=int(ui->TimeEdit->text().toDouble()/ui->TimeStepEdit->text().toDouble())+1;
    if(timenum<1 || ui->TimeEdit->text().toDouble()==this->maxt)
        return;
    this->times=timenum;
    this->maxt=ui->TimeEdit->text().toDouble();
    ui->tableWidget_value->setColumnCount(this->times+2);
    for(int i=0;i<this->times;i++)
    {
        ui->tableWidget_value->setHorizontalHeaderItem(i+2,new QTableWidgetItem("Time "+QString::number(i+1)));
        ui->tableWidget_value->setItem(0,i+2,new QTableWidgetItem(QString::number(i*this->maxt/(this->times-1))));
    }
    this->on_ResetButton_clicked();
}

void BehaviorView::on_TimeEdit_textChanged(QString )
{
    int timenum=int(ui->TimeEdit->text().toDouble()/ui->TimeStepEdit->text().toDouble())+1;
    if(timenum>this->timeNumLimit+1)
        ui->TimeEdit->setText(QString::number(ui->TimeStepEdit->text().toDouble()*this->timeNumLimit));
}
void BehaviorView::on_pushButton_Add_clicked()
{
    this->addnode();
}

void BehaviorView::on_pushButton_Delete_clicked()
{
    if(this->nodes==1||ui->tableWidget_value->currentRow()==0)
        return;
    ui->tableWidget_value->removeRow(ui->tableWidget_value->currentRow());
    this->nodes--;
}

void BehaviorView::keyPressEvent(QKeyEvent *key)
{
    if(key->key()==Qt::Key_Delete)
        this->on_pushButton_Delete_clicked();
    else if(key->key()==Qt::Key_Insert)
        this->addnode();
}
