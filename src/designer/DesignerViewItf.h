#ifndef DESIGNERVIEWITF_H
#define DESIGNERVIEWITF_H

#include <QWidget>

class DesignerMainWnd;

//! The abstract view class
class DesignerViewItf : public QWidget
{
    Q_OBJECT
public:
    DesignerViewItf(QWidget *parent, DesignerMainWnd* mainWnd)
        :QWidget(parent), mainWindow(mainWnd){}

public:
    DesignerMainWnd* mainWindow;
protected:


public:
    static DesignerViewItf* createView(QString, QWidget*);

    static QString getViewTitleByName(QString name);
    static QString getViewTitleByIndex(int index);

};

#endif // DESIGNERVIEWITF_H
