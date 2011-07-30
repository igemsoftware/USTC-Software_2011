#ifndef BEHAVIORVIEW_H
#define BEHAVIORVIEW_H

#include <QWidget>
#include <interfaces/DesignerViewItf.h>

namespace Ui {
    class BehaviorView;
}

class BehaviorView : public DesignerViewItf
{
    Q_OBJECT

public:
    int nodes;

    Q_INVOKABLE explicit BehaviorView(DesignerMainWnd *mainWnd, DesignerModelItf* model);
    ~BehaviorView();
    void prepareToPlot();
    void initiate();
    void define();
    void addnode();

private:
    Ui::BehaviorView *ui;
    bool initiated;

private slots:
    void on_tabWidget_currentChanged(int index);
    void on_tableWidget_define_cellActivated(int row, int column);
    void on_pushButton_ViewValue_clicked();
    void on_comboBox_currentIndexChanged();
    void on_pushButton_Clear_clicked();
    void on_pushButton_Draw_clicked();
    void on_pushButton_ViewGraphic_clicked();    
};

#endif // BEHAVIORVIEW_H
