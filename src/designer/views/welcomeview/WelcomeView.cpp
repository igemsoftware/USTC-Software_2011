#include "WelcomeView.h"
#include "ui_WelcomeView.h"

#include "DesignerMainWnd.h"

WelcomeView::WelcomeView(DesignerMainWnd* mainWnd, DesignerModelItf *model) :
    DesignerViewItf(mainWnd, model),
    ui(new Ui::WelcomeView)
{
    ui->setupUi(this);
    Q_ASSERT(mainWnd);

    QObject::connect(this, SIGNAL(createDocWithViewType(QString)), mainWnd, SLOT(createModelWithView(QString)));
    QObject::connect(ui->buttonOpenFile, SIGNAL(clicked()), mainWnd, SLOT(on_actionFileOpen_triggered()));
    QObject::connect(ui->buttonQuit, SIGNAL(clicked()), mainWnd, SLOT(on_actionFileExit_triggered()));
}

WelcomeView::~WelcomeView()
{
    delete ui;
}
