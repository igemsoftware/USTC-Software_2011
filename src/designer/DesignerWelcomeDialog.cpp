#include "DesignerWelcomeDialog.h"
#include "ui_DesignerWelcomeDialog.h"

WelcomeDialog::WelcomeDialog(QWidget *parent, DesignerMainWnd *mainWndValue) :
    QWidget(parent),
    mainWnd(mainWndValue),
    ui(new Ui::WelcomeDialog)
{
    ui->setupUi(this);
}

WelcomeDialog::~WelcomeDialog()
{
    delete ui;
}

void WelcomeDialog::on_buttonQuit_clicked()
{
    QApplication::quit();
}

void WelcomeDialog::on_buttonCreateAssemblyFile_clicked()
{
    if(mainWnd)
    {
        mainWnd->createView("AssemblyView");
    }
}

void WelcomeDialog::on_buttonCreateNetworkFile_clicked()
{
    if(mainWnd)
    {
        mainWnd->createView("NetworkView");
    }
}

void WelcomeDialog::on_buttonCreateBehaviorFile_clicked()
{
    if(mainWnd)
    {
        mainWnd->createView("BehaviorView");
    }
}
