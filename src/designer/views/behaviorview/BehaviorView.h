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
    int times;
    double maxc;
    double maxt;

    Q_INVOKABLE explicit BehaviorView(DesignerMainWnd *mainWnd, DesignerModelItf* model);
    ~BehaviorView();
    void prepareToPlot();
    void initiate();
    void addnode();
    void addtime();

private:
    Ui::BehaviorView *ui;
    bool initiated;

private slots:    
    void on_tableWidget_value_currentCellChanged(int currentRow, int currentColumn);
    void on_TimeNodesEdit_textChanged(QString );
    void on_generatevalueButton_clicked();
    void on_comboBox_currentIndexChanged();
    void on_pushButton_Clear_clicked();
    void on_pushButton_Draw_clicked();
    void on_ResetButton_clicked();
    void on_ConcentrationEdit_textChanged(QString );
    void on_TimeEdit_textChanged(QString );
    void on_tabWidget_currentChanged(int index);
};

#endif // BEHAVIORVIEW_H
