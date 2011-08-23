#ifndef DESIGNERDRAWWIDGET_H
#define DESIGNERDRAWWIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtGui>

class DesignerDrawWidget : public QWidget
{
    Q_OBJECT
public:

    int times;
    double maxc;
    double maxt;
    double deltat;
    QPoint currentPos;
    QColor myPenColor;
    QPoint lastPoint;
    QVector<QPoint> *vc;

    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    void evaluate(double maxc,double maxt,double deltat);
    explicit DesignerDrawWidget(QWidget *parent = 0);


public slots:
    void clearImage();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified;
    bool scribbling;
    int myPenWidth;
    QImage image;
};
#endif // DESIGNERDRAWWIDGET_H
