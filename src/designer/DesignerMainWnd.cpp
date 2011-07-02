#include <QFileDialog>
#include <QMessageBox>

#include "DesignerMainWnd.h"
#include "ui_DesignerMainWnd.h"

#include "DesignerWelcomeDialog.h"
#include "DesignerDocItf.h"


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

void DesignerMainWnd::openFileDialog()
{
    QFileDialog dlg(this, tr("Open File"));
    if(dlg.exec())
    {
        openFile(dlg.selectedFiles().first());
    }
}

void DesignerMainWnd::openFile(QString& fileName)
{
    QMetaObject* metaObject =
            DesignerDocItf::getFileFitsDocumentTypesStatus(fileName);
    if(!metaObject)
    {
        QMessageBox msgBox(QMessageBox::Critical,
                           tr("Lachesis Designer"),
                           tr("Cannot recognize the file yet."),
                           QMessageBox::Ok,
                           this);
        msgBox.exec();
        return;
    }

    DesignerMainWnd* pFrame = (currentDoc ? this : globalCreateNewMainWnd());
    DesignerDocItf*  pDoc   = (DesignerDocItf*)metaObject->newInstance(
                Q_ARG(DesignerMainWnd*, pFrame));
    if(pDoc)
    {
        QFile file(fileName);
        pDoc->loadFromFile(file);
    }
}

//Top level main window list.
QList<DesignerMainWnd*> DesignerMainWnd::mainWnd_list;

DesignerMainWnd* DesignerMainWnd::globalCreateNewMainWnd()
{
    DesignerMainWnd* pFrame = new DesignerMainWnd();
    pFrame->show();
    mainWnd_list.append(pFrame);
    return pFrame;
}

void DesignerMainWnd::globalUnregisterMainWnd(DesignerMainWnd* pFrame)
{
    if(pFrame)
    {
        mainWnd_list.removeAll(pFrame);
    }
}

void DesignerMainWnd::on_action_Open_File_triggered()
{
    openFileDialog();
}
