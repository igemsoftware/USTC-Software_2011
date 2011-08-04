#ifndef PARTVIEW_H
#define PARTVIEW_H

#include "interfaces/DesignerViewItf.h"
#include "ui_PartView.h"

namespace Ui {
    class PartView;
}

class PartView : public DesignerViewItf
{
    Q_OBJECT

public:
    int listviewindex;
    Q_INVOKABLE explicit PartView(DesignerMainWnd *mainWnd, DesignerModelItf* model);
    ~PartView();

private:
    Ui::PartView *ui;

private slots:
    void on_pushButton_clicked();
    void on_listView_clicked(QModelIndex index);
};

#endif // PARTVIEW_H
