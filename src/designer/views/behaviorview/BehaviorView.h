#ifndef BEHAVIORVIEW_H
#define BEHAVIORVIEW_H

#include <QWidget>
#include "interfaces/DesignerViewItf.h"

namespace Ui {
    class BehaviorView;
}

class BehaviorView : public DesignerViewComponent
{
    Q_OBJECT

public:
    int nodes;
    int times;
    int timeNumLimit;
    double maxc;
    double maxt;   

    Q_INVOKABLE explicit BehaviorView(DesignerMainWnd *mainWnd, DesignerModelComponent* model);
    ~BehaviorView();
    virtual void updateFeatureToolbar(QToolBar *toolBar);
    void prepareToPlot();
    void initiate();
    void addnode();
    void addtime();
    void keyPressEvent(QKeyEvent *key);
    bool eventFilter(QObject *, QEvent *);

private:
    Ui::BehaviorView *ui;
    bool initiated;

private slots:    
    void on_TimeStepEdit_textChanged(QString );
    void on_TimeEdit_textChanged(QString );
    void on_pushButton_Delete_clicked();
    void on_pushButton_Add_clicked();
    void on_TimeEdit_editingFinished();
    void on_TimeStepEdit_editingFinished();
    void on_generatevalueButton_clicked();
    void on_comboBox_currentIndexChanged();
    void on_pushButton_Clear_clicked();
    void on_pushButton_Draw_clicked();
    void on_ResetButton_clicked();
    void on_ConcentrationEdit_editingFinished();
    void on_tabWidget_currentChanged(int index);
    void showDialog();
};

#endif // BEHAVIORVIEW_H
