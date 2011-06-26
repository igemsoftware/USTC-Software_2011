#include "DesignerMainWnd.h"
#include "ui_DesignerMainWnd.h"

#include "DesignerWelcomeDialog.h"

DesignerMainWnd::DesignerMainWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DesignerMainWnd)
{
    ui->setupUi(this);
    if((welcomeDialog = new WelcomeDialog(centralWidget(), this)))
        welcomeDialog->show();
    currentView = NULL;
}

DesignerMainWnd::~DesignerMainWnd()
{
    delete ui;
}

void DesignerMainWnd::resizeEvent ( QResizeEvent * event )
{
    if(welcomeDialog)
    {
        welcomeDialog->move((centralWidget()->width() - welcomeDialog->width())/2, (centralWidget()->height()-welcomeDialog->height())/2);
    }
    if(currentView)
    {
        currentView->resize(centralWidget()->size());
    }
}

void DesignerMainWnd::closeEvent  ( QCloseEvent  * event )
{


    globalUnregisterMainWnd(this);
    this->deleteLater();
    return;
}


void DesignerMainWnd::on_action_New_File_activated(int )
{
    globalCreateNewMainWnd();
}


void DesignerMainWnd::createView(QString viewName)
{
    if(welcomeDialog)
    {
        welcomeDialog->close();
        welcomeDialog->deleteLater();
        welcomeDialog=NULL;
    }

    DesignerViewItf *view =
            DesignerViewItf::createView(viewName, centralWidget());

    if(view)
    {
        currentView = view;
        view->setGeometry(0, 0, centralWidget()->width(), centralWidget()->height());
        view->show();
    }
}

//Top level main window list.
QList<DesignerMainWnd*> DesignerMainWnd::mainWnd_list;

void DesignerMainWnd::globalCreateNewMainWnd()
{
    DesignerMainWnd* pFrame = new DesignerMainWnd();
    pFrame->show();
    mainWnd_list.append(pFrame);
}

void DesignerMainWnd::globalUnregisterMainWnd(DesignerMainWnd* pFrame)
{
    if(pFrame)
    {
        mainWnd_list.removeAll(pFrame);
    }
}
