#include "FileDescriptionView.h"
#include "ui_FileDescriptionView.h"
#include "common/mainwnd/DesignerMainWnd.h"
#include "interfaces/DesignerInterface.h"

FileDescriptionView::FileDescriptionView(DesignerMainWnd* mainWnd, DesignerModelComponent *model) :
    DesignerViewComponent(mainWnd, model),
    ui(new Ui::FileDescriptionView)
{
    ui->setupUi(this);

    QStringList viewList = mainWnd->getCurrentModel()->getSupportedViewList();
    for(int i=0;i<viewList.count();i++)
    {
        QListWidgetItem *newItem = new QListWidgetItem(DesignerViewComponent::getViewTitleByName(viewList[i]));
        newItem->setData(1, (QVariant)viewList[i]);
        ui->listViews->addItem(newItem);
    }    

    connect(model, SIGNAL(storageUpdated()), SLOT(storageUpdated()));
    storageUpdated();
    emit updateSelectedItem(mainWnd->getCurrentModel()->getModel());
}

FileDescriptionView::~FileDescriptionView()
{
    delete ui;
}

void FileDescriptionView::storageUpdated()
{
    QPixmap pic(":/designer/fileicons/documents/"+QString(currentModel->getCurrentDoc()->metaObject()->className()).toLower().remove("doc")+".png");
    if(!pic.isNull()){
        ui->labelImage->setPixmap(pic);
    }
    if(currentModel->getCurrentDoc())
    {
        ui->labelFileName->setText(currentModel->getCurrentDoc()->getDocumentFileInfo().fileName());
        ui->labelFileSize->setText(QString::number(currentModel->getCurrentDoc()->getDocumentFileInfo().size()));
        ui->labelFilePath->setText(currentModel->getCurrentDoc()->getDocumentFileInfo().filePath());
    	ui->labelLastModified->setText(currentModel->getCurrentDoc()->getDocumentFileInfo().lastModified().toString());
    	ui->labelLastRead->setText(currentModel->getCurrentDoc()->getDocumentFileInfo().lastRead().toString());
    }
    else
    {
        ui->labelFileName->setText(tr("<Not saved>"));
        ui->labelFileSize->setText(tr("<Not saved>"));
        ui->labelFilePath->setText(tr("<Not saved>"));
	ui->labelLastModified->setText(tr("<Not saved>"));
	ui->labelLastRead->setText(tr("<Not saved>"));
    }
    ui->labelFileType->setText(DesignerDocMgr::getDocTypeTitle(currentModel->getCurrentDoc()->metaObject()->className()));
}

void FileDescriptionView::on_listViews_itemClicked(QListWidgetItem *item)
{
    mainWindow->createView(item->data(1).toString());
}
