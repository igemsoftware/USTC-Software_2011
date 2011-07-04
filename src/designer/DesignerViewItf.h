#ifndef DESIGNERVIEWITF_H
#define DESIGNERVIEWITF_H

#include <QWidget>


//! The abstract view class
class DesignerViewItf : public QWidget
{
    Q_OBJECT
public:
    DesignerViewItf(QWidget *parent):QWidget(parent){}


protected:


public:
    static DesignerViewItf* createView(QString, QWidget*);

    static QString getViewTitleByName(QString name);
    static QString getViewTitleByIndex(int index);

};

#endif // DESIGNERVIEWITF_H
