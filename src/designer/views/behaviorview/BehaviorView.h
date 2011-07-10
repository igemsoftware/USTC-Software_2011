#ifndef BEHAVIORVIEW_H
#define BEHAVIORVIEW_H

#include <QWidget>
#include <DesignerViewItf.h>

namespace Ui {
    class BehaviorView;
}

class BehaviorView : public DesignerViewItf
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit BehaviorView(DesignerMainWnd *mainWnd);
    ~BehaviorView();
    void prepareToPlot();

private:
    Ui::BehaviorView *ui;
    bool defined,initiated;

private slots:    
    void on_pushButton_ViewValue_clicked();
    void on_comboBox_currentIndexChanged();
    void on_pushButton_Clear_clicked();
    void on_pushButton_Draw_clicked();
    void on_pushButton_ViewGraphic_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // BEHAVIORVIEW_H
