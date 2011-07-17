#ifndef CLOTHODBVIEW_H
#define CLOTHODBVIEW_H

#include <QtGui>
#include <QtCore>
#include <QtXml>

#include "interfaces/DesignerViewItf.h"


namespace Ui {
    class ClothoDBView;
}

class ClothoDBView : public DesignerViewItf
{
    Q_OBJECT
    QDomDocument doc;


public:
    void initiate();
    void connect();

    Q_INVOKABLE explicit ClothoDBView(DesignerMainWnd *mainWnd);
    ~ClothoDBView();

private:
    Ui::ClothoDBView *ui;

private slots:
    void on_treeView_doubleClicked(QModelIndex index);
    void on_pushButton_clicked();
};

#endif // CLOTHODBVIEW_H
