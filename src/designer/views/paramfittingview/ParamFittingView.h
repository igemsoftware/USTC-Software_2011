#ifndef PARAMFITTINGVIEW_H
#define PARAMFITTINGVIEW_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QSplitter>
#include "qwt_plot.h"

#include "interfaces/DesignerViewComponent.h"

namespace Ui {
    class ParamFittingView;
}

class ParamFittingView : public DesignerViewComponent
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit ParamFittingView(DesignerMainWnd *mainWnd, DesignerModelComponent* model);
    ~ParamFittingView();

private:
    Ui::ParamFittingView *ui;
    QwtPlot *result_plot, *progress_plot;
    QTableWidget *parameter_table;

};

#endif // PARAMFITTINGVIEW_H
