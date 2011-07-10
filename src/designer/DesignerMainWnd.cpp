#include <QFileDialog>
#include <QMessageBox>

#include "DesignerMainWnd.h"
#include "ui_DesignerMainWnd.h"

#include "views/welcomeview/WelcomeView.h"

#include "DesignerChooseViewDialog.h"
#include "DesignerDocItf.h"


DesignerMainWnd::DesignerMainWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DesignerMainWnd)
{
    ui->setupUi(this);

    currentDoc = NULL;
    updateTabInfo();
}

DesignerMainWnd::~DesignerMainWnd()
{
    delete ui;
}

void DesignerMainWnd::resizeEvent ( QResizeEvent * event )
{
/*    if(welcomeDialog)
    {
        welcomeDialog->move((centralWidget()->width() - welcomeDialog->width())/2, (centralWidget()->height()-welcomeDialog->height())/2);
    }
    if(currentView)
    {
        currentView->resize(centralWidget()->size());
    }*/
}

void DesignerMainWnd::updateTabInfo()
{
    if(!currentDoc)
    {
        if(ui->tabWidget->count()==0)
        {
            DesignerViewItf* welcomeView = DesignerViewItf::createView("WelcomeView", this);
            Q_ASSERT(welcomeView);
            int tabIndex = ui->tabWidget->addTab(welcomeView, QString("Welcome"));
            ui->tabWidget->protectPage(tabIndex);
        }
    }
}

void DesignerMainWnd::closeEvent  ( QCloseEvent  * event )
{
    globalUnregisterMainWnd(this);
    this->deleteLater();
    return;
}

void DesignerMainWnd::createView(QString viewName)
{
    for(int i = 0; i < ui->tabWidget->count(); i++)
    {
        if(ui->tabWidget->widget(i)
                && (QString(ui->tabWidget->widget(i)->metaObject()->className())
                == "WelcomeView"))
        {
            ui->tabWidget->removeTab(i);
            break;
        }
    }

    DesignerViewItf *view =
            DesignerViewItf::createView(viewName, this);

    if(view)
    {
        ui->tabWidget->addTab(view, DesignerViewItf::getViewTitleByName(viewName));
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

    DesignerMainWnd* pFrame = (currentDoc ? globalCreateNewMainWnd() : this);
    DesignerDocItf*  pDoc   = (DesignerDocItf*)metaObject->newInstance();
    if(!pDoc)
    {
        QMessageBox msgBox(QMessageBox::Critical,
                           tr("Lachesis Designer"),
                           tr("We encountered an error."),
                           QMessageBox::Ok,
                           pFrame);

        msgBox.exec();
        pFrame->deleteLater();
        pDoc->deleteLater();
        return;
    }

    QFile file(fileName);
    if(!pDoc->loadFromFile(file))
    {
        file.close();
        QMessageBox msgBox(QMessageBox::Critical,
                           tr("Lachesis Designer"),
                           tr("We encountered an error."),
                           QMessageBox::Ok,
                           pFrame);
        msgBox.exec();
        pFrame->deleteLater();
        return;
    }
    file.close();

    QList<QString> viewList = pDoc->getSupportedViewList();
    QString viewName;
    if(viewList.count()==0)
    {
        QMessageBox msgBox(QMessageBox::Critical,
                           tr("Lachesis Designer"),
                           tr("This file format seems supported, while there's no way to display it. "),
                           QMessageBox::Ok,
                           pFrame);
        msgBox.exec();
        return;
    }
    else if(viewList.count()==1)
    {
        viewName = viewList[0];
    }
    else
    {
        ChooseViewDialog chooseViewdlg(pFrame, viewList);
        if(chooseViewdlg.exec()==QDialog::Accepted)
        {
            viewName=viewList[chooseViewdlg.getChoosenViewIndex()];
        }
    }
    if(!viewName.isNull())
    {
        pFrame->currentDoc = pDoc;
        pFrame->createView(viewName);
    }

    updateTabInfo();
}

//Top level main window list.
QList<DesignerMainWnd*> DesignerMainWnd::mainWnd_list;

DesignerMainWnd* DesignerMainWnd::globalCreateNewMainWnd()
{
    DesignerMainWnd* pFrame = new DesignerMainWnd();
    pFrame->showMaximized();
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

DesignerDocItf * DesignerMainWnd::getCurrentDoc(QString defaultDocType)
{
    if(currentDoc)
        return currentDoc;
    return (currentDoc = DesignerDocItf::createEmptyDoc(defaultDocType));
}


void DesignerMainWnd::on_actionFileNew_triggered()
{
    globalCreateNewMainWnd();
}

void DesignerMainWnd::on_actionFileOpen_triggered()
{
    QFileDialog dlg(this, tr("Open File"));
    if(dlg.exec())
    {
        openFile(dlg.selectedFiles().first());
    }
}

void DesignerMainWnd::on_actionFileSave_triggered()
{

}


void DesignerMainWnd::on_actionFileExit_triggered()
{
    QApplication::quit();
}

