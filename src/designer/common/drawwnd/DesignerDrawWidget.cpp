#include "DesignerDrawWidget.h"

DesignerDrawWidget::DesignerDrawWidget(QWidget *parent) :
    QWidget(parent)
{
    this->maxt=10;
    this->deltat=1;
    this->maxc=10;
    this->myPenWidth=1;
    this->myPenColor=Qt::red;
        this->vc=new QVector<QPair<double,double> >();
}
void DesignerDrawWidget::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void DesignerDrawWidget::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void DesignerDrawWidget::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

void DesignerDrawWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton  && event->x()>30 && event->y()<(this->size().height()-10)) {
        lastPoint = event->pos();
        scribbling = true;
        this->vc->clear();
        this->currentPos=event->pos();
    }
}

void DesignerDrawWidget::mouseMoveEvent(QMouseEvent *event)
{
    double deltax=this->deltat*(this->size().width()-40)/this->maxt;
    int index=int((this->currentPos.x()-30)/deltax)+1;
    if ((event->buttons() & Qt::LeftButton) && scribbling  && event->x()>30 && event->y()<(this->size().height()-10))
        drawLineTo(event->pos());
    if (this->scribbling)
    {
        while(int((event->pos().x()-30)/deltax)>=index)
        {
            int x1=this->currentPos.x(),x2=event->pos().x();
            int y1=this->currentPos.y(),y2=event->pos().y();
            int x=index*deltax+30;
            int y=int((y1*x2+y2*x-y1*x-y2*x1)/(x2-x1));
            QPoint temp(x,y);
            vc->append(transCoordinate(temp));
            index++;
        }
        this->currentPos=event->pos();
    }
}

void DesignerDrawWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling && event->x()>30 && event->y()<(this->size().height()-10)) {
        drawLineTo(event->pos());
        scribbling = false;
    }
}

void DesignerDrawWidget::paintEvent(QPaintEvent *event)
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
            painter.drawText(i*(width-40)/10+25,height,QString::number(i*this->maxt/10));
        }
        for(int i=0;i<10;i++)
        {
            painter.drawText(0,i*(height-20)/10+15,QString::number((10-i)*this->maxc/10));
        }
    }
}

void DesignerDrawWidget::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void DesignerDrawWidget::drawLineTo(const QPoint &endPoint)
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

void DesignerDrawWidget::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void DesignerDrawWidget::evaluate(double maxc, double maxt, double deltat)
{
    this->maxc=maxc;
    this->maxt=maxt;
    this->deltat=deltat;
    this->clearImage();
    this->repaint();
}

QPair<double,double>  DesignerDrawWidget::transCoordinate(QPoint p)
{
    double x=(p.x()-30.0)/(size().width()-40.0)*maxt;
    double y=maxc-(p.y()-10.0)*maxc/(size().height()-20.0);
    return *(new QPair<double,double>(x,y));
}
