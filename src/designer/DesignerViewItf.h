#ifndef DESIGNERVIEWITF_H
#define DESIGNERVIEWITF_H

#include <QtGui>

class DesignerMainWnd;

//! The abstract view class
class DesignerViewItf : public QWidget
{
    Q_OBJECT
public:
    DesignerViewItf(DesignerMainWnd* mainWnd)
        :QWidget(), mainWindow(mainWnd){}

public:
    DesignerMainWnd* mainWindow;
protected:


public:
    static DesignerViewItf* createView(QString, DesignerMainWnd* mainWnd);

    static QString getViewTitleByName(QString name);
    static QMetaObject getViewMetaObjectByName(QString name);

};

#endif // DESIGNERVIEWITF_H
