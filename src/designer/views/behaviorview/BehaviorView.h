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
    void on_tabWidget_currentChanged(int index);
    void on_tableWidget_value_cellActivated(int row, int column);
};

#endif // BEHAVIORVIEW_H
