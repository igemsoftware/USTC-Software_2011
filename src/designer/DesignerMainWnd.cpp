#include <QFileDialog>
#include <QMessageBox>

#include "DesignerMainWnd.h"
#include "ui_DesignerMainWnd.h"

#include "views/welcomeview/WelcomeView.h"

#include "DesignerDocItf.h"

#if defined( Q_OS_WIN )
#include <windows.h>
#endif

DesignerMainWnd::DesignerMainWnd(QWidget *parent) :
    QMainWindow(parent),
    currentDoc(NULL),
    ui(new Ui::DesignerMainWnd)
{
    ui->setupUi(this);

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

QWidget* DesignerMainWnd::getPanelWidget(QString panelName)
{
    if(panelName=="PropertiesPanel")
    {
        return ui->propertiesPanelWidget;
    }
    return NULL;
}

void DesignerMainWnd::updateTabInfo()
{
    if(!currentDoc)
    {
        if(ui->tabWidget->count()==0) createView("WelcomeView", true);
    }
}

void DesignerMainWnd::closeEvent  ( QCloseEvent  * event )
{
    globalUnregisterMainWnd(this);
    this->deleteLater();
    return;
}

void DesignerMainWnd::createView(QString viewName, bool isProtected)
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
        int tabIndex = ui->tabWidget->addTab(view, DesignerViewItf::getViewTitleByName(viewName));
        if(isProtected) ui->tabWidget->protectTab(tabIndex);
        ui->tabWidget->setCurrentIndex(tabIndex);
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
        pDoc->deleteLater();
        return;
    }
    file.close();

    pFrame->currentDoc = pDoc;
    pFrame->createView("FileDescriptionView", true);
/*
*/
    updateTabInfo();
}

//Top level main window list.
QList<DesignerMainWnd*> DesignerMainWnd::mainWnd_list;

DesignerMainWnd* DesignerMainWnd::globalCreateNewMainWnd()
{
    DesignerMainWnd* pFrame = new DesignerMainWnd();
    pFrame->showMaximized();
    pFrame->raise();
    pFrame->activateWindow();

#if defined( Q_OS_WIN )
    SetWindowPos( pFrame->winId(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
    SetWindowPos( pFrame->winId(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
#endif

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

void DesignerMainWnd::instanceMessageReceived(const QString& message)
{
    if(message=="/new")
    {
        globalCreateNewMainWnd();
    }
}

void DesignerMainWnd::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}
