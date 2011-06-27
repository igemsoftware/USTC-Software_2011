#ifndef DESIGNERBEHAVIORVIEW_H
#define DESIGNERBEHAVIORVIEW_H

#include <QWidget>
#include <DesignerViewItf.h>

namespace Ui {
    class BehaviorView;
}

class BehaviorView : public DesignerViewItf
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit BehaviorView(QWidget *parent = 0);
    ~BehaviorView();

private:
    Ui::BehaviorView *ui;
};

#endif // DESIGNERBEHAVIORVIEW_H
