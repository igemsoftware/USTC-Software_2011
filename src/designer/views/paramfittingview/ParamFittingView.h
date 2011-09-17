#ifndef PARAMFITTINGVIEW_H
#define PARAMFITTINGVIEW_H

#include <QWidget>

namespace Ui {
    class ParamFittingView;
}

class ParamFittingView : public QWidget
{
    Q_OBJECT

public:
    explicit ParamFittingView(QWidget *parent = 0);
    ~ParamFittingView();

private:
    Ui::ParamFittingView *ui;
};

#endif // PARAMFITTINGVIEW_H
