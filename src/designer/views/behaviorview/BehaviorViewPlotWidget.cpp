#include "BehaviorViewPlotWidget.h"
#include <QtGui>

BehaviorViewPlotWidget::BehaviorViewPlotWidget(QWidget *parent) :
    QWidget(parent)
{
    this->drawable=false;
    this->myPenWidth=1;
    this->myPenColor=Qt::red;
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
    if (event->button() == Qt::LeftButton && this->drawable && event->x()>20 && event->y()<(this->size().height()-10)) {
        lastPoint = event->pos();
        scribbling = true;
    }
}

void BehaviorViewPlotWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling && this->drawable && event->x()>20 && event->y()<(this->size().height()-10))
        drawLineTo(event->pos());
}

void BehaviorViewPlotWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling && this->drawable && event->x()>20 && event->y()<(this->size().height()-10)) {
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
        painter.drawLine(20,10,20,height-10);
        painter.drawLine(20,height-10,width-10,height-10);
        painter.drawText(30,15,tr("c(mol/L)"));
        painter.drawText(width-40,height-15,tr("Time(s)"));
        //draw marks
        for(int i=0;i<10;i++)
        {
            painter.drawText(i*(width-30)/10+5,height,QString::number(this->deltax*i*(this->x-1)/10));
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


