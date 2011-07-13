#include "BehaviorViewPlotWidget.h"

BehaviorViewPlotWidget::BehaviorViewPlotWidget(QWidget *parent) :
    QWidget(parent)
{
    this->drawable=false;
    this->maxy=0;
    this->myPenWidth=1;
    this->myPenColor=Qt::red;
    this->vc=new QVector<QPoint>();
}
void BehaviorViewPlotWidget::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void BehaviorViewPlotWidget::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;    
}

void BehaviorViewPlotWidget::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

void BehaviorViewPlotWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && this->drawable && event->x()>30 && event->y()<(this->size().height()-10)) {
        lastPoint = event->pos();
        scribbling = true;
        this->currentPos=event->pos();
    }
}

void BehaviorViewPlotWidget::mouseMoveEvent(QMouseEvent *event)
{
    int total=int(this->maxx/this->deltax),index=int((this->currentPos.x()-30)/this->deltax)+1;
    int i=(event->x()-30)%int(this->deltax*(this->size().width()-40)/this->maxx);
    if ((event->buttons() & Qt::LeftButton) && scribbling && this->drawable && event->x()>30 && event->y()<(this->size().height()-10))
        drawLineTo(event->pos());
    if (this->drawable)
    {
        if(i==0)
        {
            vc->append(event->pos());
            index++;
        }
        else if(int((event->pos().x()-30)/this->deltax)>=index)
        {
            int x1=this->currentPos.x(),x2=event->pos().x();
            int y1=this->currentPos.y(),y2=event->pos().y();
            int x=index*this->deltax+30;
            int y=int((y1*x2+y2*x-y1*x-y2*x1)/(x2-x1));
            QPoint *temp=new QPoint(x,y);
            vc->append(*temp);
            index++;
        }
        this->currentPos=event->pos();
    }
}

void BehaviorViewPlotWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling && this->drawable && event->x()>30 && event->y()<(this->size().height()-10)) {
        drawLineTo(event->pos());
        scribbling = false;
    }
}

void BehaviorViewPlotWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    //draw axises and the main image
    {
        int width=this->size().width();
        int height=this->size().height();
        painter.drawImage(dirtyRect, image, dirtyRect);
        painter.drawLine(30,10,30,height-10);
        painter.drawLine(30,height-10,width-10,height-10);
        painter.drawText(50,10,tr("c(mol/L)"));
        painter.drawText(width-40,height-15,tr("Time(s)"));
        //draw marks
        for(int i=0;i<10;i++)
        {
            painter.drawText(i*(width-40)/10+25,height,QString::number(this->deltax*i*(this->x-1)/10));
        }
        for(int i=0;i<10;i++)
        {
            painter.drawText(0,i*(height-20)/10+15,QString::number((10-i)*this->maxy/10));
        }
    }
}

void BehaviorViewPlotWidget::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void BehaviorViewPlotWidget::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));    
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void BehaviorViewPlotWidget::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void BehaviorViewPlotWidget::PlotFromValue()
{
    this->clearImage();
    for(int i=0;i<this->node;i++)
    {

        if(this->cb->currentIndex()==i||this->cb->currentIndex()==(this->cb->count()-1))
        {
            QComboBox *comboBox=(QComboBox *)this->tab_1->cellWidget(i,1);
            this->myPenColor=comboBox->itemData(comboBox->currentIndex(), Qt::UserRole).value<QColor>();
            for(int j=0;j<this->x;j++)
            {
                    int height=this->size().height()-20;
                    int width=this->size().width()-40;
                    double value;
                    if(this->tab_2->item(j,i+1)!=NULL)
                    {
                        value=this->tab_2->item(j,i+1)->text().toDouble();
                        QPoint *pt=new QPoint(int(30+this->tab_2->item(j,0)->text().toDouble()*width/this->maxx),int(10+(this->maxy-value)*height/this->maxy));
                        if(j==0)
                        {
                            this->lastPoint=*pt;
                        }
                        this->drawLineTo(*pt);
                    }
            }
        }
    }
}

