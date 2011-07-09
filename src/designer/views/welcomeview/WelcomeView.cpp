#include "WelcomeView.h"
#include "ui_WelcomeView.h"

#include "DesignerMainWnd.h"

WelcomeView::WelcomeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeView)
{
    ui->setupUi(this);
}

WelcomeView::~WelcomeView()
{
    delete ui;
}

void WelcomeView::on_buttonQuit_clicked()
{
    QApplication::quit();
}

void WelcomeView::on_buttonCreateAssemblyFile_clicked()
{
    if(mainWnd)
    {
        mainWnd->createView("AssemblyView");
    }
}

void WelcomeView::on_buttonCreateNetworkFile_clicked()
{
    if(mainWnd)
    {
        mainWnd->createView("NetworkView");
    }
}

void WelcomeView::on_buttonCreateBehaviorFile_clicked()
{
    if(mainWnd)
    {
        mainWnd->createView("BehaviorView");
    }
}

void WelcomeView::on_buttonOpenFile_clicked()
{
    if(mainWnd)
    {
        mainWnd->openFileDialog();
    }
}
