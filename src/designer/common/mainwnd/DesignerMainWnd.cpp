#include <QFileDialog>
#include <QMessageBox>

#include "common/mainwnd/DesignerMainWnd.h"
#include "ui_DesignerMainWnd.h"

#include "views/welcomeview/WelcomeView.h"

#include "interfaces/DesignerInterface.h"

#if defined( Q_OS_WIN )
#include <windows.h>
#endif

DesignerMainWnd::DesignerMainWnd(QWidget *parent) :
    QMainWindow(parent),
    currentModel(NULL),
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
    if(!currentModel)
    {
        if(ui->tabWidget->count()==0) createView("WelcomeView", true);
    }
}

void DesignerMainWnd::removeTabWithClass(QString className)
{
    for(int i = 0; i < ui->tabWidget->count(); i++)
    {
        QWidget* widget = ui->tabWidget->widget(i);
        if(widget->metaObject()->className()==className)
        {
            ui->tabWidget->removeTab(i);
            i--;
        }
    }
}
void DesignerMainWnd::createView(QString viewName, bool isProtected)
{
    createView(viewName, isProtected, currentModel);
}

void DesignerMainWnd::createView(QString viewName, bool isProtected, DesignerModelComponent* model)
{
    DesignerViewComponent *view =
            DesignerViewMgr::createView(viewName, this, model);

    if(view)
    {
        int tabIndex = ui->tabWidget->addTab(view, DesignerViewMgr::getViewTitleByName(viewName));
        if(isProtected) ui->tabWidget->protectTab(tabIndex);
        ui->tabWidget->setCurrentIndex(tabIndex);
    }

    if(currentModel)
    {
        removeTabWithClass("WelcomeView");
    }

}

void DesignerMainWnd::createModelWithView(QString viewName)
{
    QString modelName = DesignerViewMgr::getViewDefaultModelByName(viewName);
    currentModel = DesignerModelMgr::createModel(modelName);
    createView(viewName);
}

void DesignerMainWnd::openFile(QString& fileName)
{
    const QMetaObject* metaObject =
            DesignerDocMgr::getBestFitDocumentTypeForFile(fileName);
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

    DesignerMainWnd* pFrame = (currentModel ? globalCreateNewMainWnd() : this);
    DesignerDocComponent*  pDoc   = (DesignerDocComponent*)metaObject->newInstance();
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

    if(!pDoc->loadFromDiskFile(fileName))
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

    pFrame->currentModel = pDoc->getCurrentModel();
    pFrame->createView("FileDescriptionView", true);
/*
*/
    updateTabInfo();
}

void DesignerMainWnd::closeEvent(QCloseEvent *event)
{
    QMessageBox msgbox(
                QMessageBox::NoIcon,
                tr("Lachesis Designer"),
                tr("Your file \'%1\' is modified, do you want to save it?").arg(""),
                QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,
                this
                );
    while(getCurrentModel()&& getCurrentModel()->isModified())
    {
        int retValue = msgbox.exec();
        if(retValue == QMessageBox::Yes)
        {
            on_actionFileSave_triggered();
        }
        else if(retValue == QMessageBox::No)
        {
            globalUnregisterMainWnd(this);
            event->accept();
            return;
        }
        else
        {
            event->ignore();
            return;
        }
    }
    globalUnregisterMainWnd(this);
    event->accept();
}

void DesignerMainWnd::saveFile(QString& fileName, QString docTypeName)
{
    DesignerDocComponent* newDoc =
            DesignerDocMgr::createEmptyDoc(docTypeName, getCurrentModel());
    if(newDoc)
    {
        DesignerDocComponent* oldDoc = currentModel->getCurrentDoc();
        currentModel->setCurrentDoc(newDoc);
        if(newDoc->saveToDiskFile(fileName))
        {
            if(oldDoc) oldDoc->deleteLater();
        }
        else
        {
            currentModel->setCurrentDoc(oldDoc);
        }
    }
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

DesignerDocComponent * DesignerMainWnd::getCurrentDoc(QString defaultDocType)
{
    return currentModel->getCurrentDoc();
}


void DesignerMainWnd::on_actionFileNew_triggered()
{
    globalCreateNewMainWnd();
}

void DesignerMainWnd::on_actionFileOpen_triggered()
{
    QFileDialog dlg(this, tr("Open File"));
    QStringList doclist = DesignerDocMgr::getDocTypeList();
    QStringList filterlist;
    filterlist<< "All Files (*.*)";
    for(int i=0;i<doclist.count();i++)
    {
        filterlist << DesignerDocMgr::getDocTypeFilter(doclist[i]);
    }
    dlg.setFileMode(QFileDialog::ExistingFile);
    dlg.setNameFilters(filterlist);

    if(dlg.exec()==QDialog::Accepted)
    {
        openFile(dlg.selectedFiles().first());
    }
}

void DesignerMainWnd::on_actionFileSave_triggered()
{
    if(!getCurrentModel()) return;
    if(!getCurrentModel()->getCurrentDoc()||
            getCurrentModel()->getCurrentDoc()->isReadOnly()||
            !DesignerDocMgr::isDocTypeSaveSupported(getCurrentModel()->getCurrentDoc()->metaObject()->className())
            )
    {
        on_actionFileSaveAs_triggered();
    }
    else
    {
        getCurrentModel()->getCurrentDoc()->updateFile();
    }
    updateTabInfo();
}


void DesignerMainWnd::on_actionFileSaveAs_triggered()
{
    QFileDialog dlg(this, tr("Save File"));
    dlg.setAcceptMode(QFileDialog::AcceptSave);

    QStringList doclist = getCurrentModel()->getSupportedDocumentList();
    QStringList filters;
    for(int i=0;i<doclist.count();i++)
    {
        if(!DesignerDocMgr::isDocTypeSaveSupported(doclist[i]))
        {
            doclist.removeAt(i);
            i--;
        }
        else
        {
            filters << DesignerDocMgr::getDocTypeFilter(doclist[i]);
        }
    }

    dlg.setNameFilters(filters);

    if(dlg.exec()==QDialog::Accepted)
    {
        if(dlg.selectedFiles().size())
        {
            int filterIndex = filters.indexOf(dlg.selectedNameFilter());
            saveFile(dlg.selectedFiles()[0], doclist[filterIndex]);
        }
    }
}


void DesignerMainWnd::on_actionFileExit_triggered()
{
    QApplication::quit();
}

void DesignerMainWnd::on_actionHelpAboutApp_triggered()
{
    createView("AboutView");
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
    if( ui->tabWidget->count() == 0 ) this->close();
}

void DesignerMainWnd::on_tabWidget_currentChanged(QWidget *arg1)
{
    ui->featureToolBar->actions().clear();
    DesignerViewItf *viewItf;
    if(arg1 && (viewItf = qobject_cast<DesignerViewItf*>(arg1)))
    {
        ui->featureToolBar->clear();
        viewItf->updateFeatureToolbar(ui->featureToolBar);
    }
}
