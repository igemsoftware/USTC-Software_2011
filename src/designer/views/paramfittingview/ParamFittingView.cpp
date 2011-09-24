#include "ParamFittingView.h"
#include "ui_ParamFittingView.h"

ParamFittingView::ParamFittingView(DesignerMainWnd *mainWnd, DesignerModelComponent *model) :
    DesignerViewComponent(mainWnd, model),
    ui(new Ui::ParamFittingView)
{
    ui->setupUi(this);

    QSplitter *vertical = new QSplitter(Qt::Vertical);
    QSplitter *horizontal = new QSplitter(Qt::Horizontal);
    QVBoxLayout *layout = new QVBoxLayout;

    horizontal->addWidget( parameter_table = new QTableWidget );
    horizontal->addWidget( result_plot = new QwtPlot );

    vertical->addWidget(horizontal);
    vertical->addWidget( progress_plot = new QwtPlot );

    layout->addWidget(vertical);
    setLayout(layout);
}

ParamFittingView::~ParamFittingView()
{
    delete ui;
}
