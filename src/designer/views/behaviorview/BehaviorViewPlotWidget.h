#ifndef BEHAVIORVIEWPLOTWIDGET_H
#define BEHAVIORVIEWPLOTWIDGET_H

#include <QtGui>
#include "BehaviorViewInterp.h"

class BehaviorViewPlotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BehaviorViewPlotWidget(QWidget *parent = 0);
    bool drawable;
    int nodes;
    int times;
    double maxc;
    double maxt;
    double deltat;
    QPushButton *draw;
    QPoint currentPos;
    QVector<QPoint> *vc;
    QColor myPenColor;
    QTableWidget *tab;
    QComboBox *cb;

    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    void PlotFromValue();
    void ValueFromPlot();
    QVector<double> * spline(QVector<double> *t, QVector<double> *c, QVector<double> *newt);
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
    QPoint lastPoint;

};

#endif // BEHAVIORVIEWPLOTWIDGET_H
