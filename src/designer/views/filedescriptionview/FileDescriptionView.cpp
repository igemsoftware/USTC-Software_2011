#include "FileDescriptionView.h"
#include "ui_FileDescriptionView.h"
#include "DesignerMainWnd.h"
#include "interfaces/DesignerInterface.h"

FileDescriptionView::FileDescriptionView(DesignerMainWnd* mainWnd, DesignerModelItf *model) :
    DesignerViewItf(mainWnd, model),
    ui(new Ui::FileDescriptionView)
{
    ui->setupUi(this);

    QStringList viewList = mainWnd->getCurrentModel()->getSupportedViewList();
    for(int i=0;i<viewList.count();i++)
    {
        QListWidgetItem *newItem = new QListWidgetItem(DesignerViewItf::getViewTitleByName(viewList[i]));
        newItem->setData(1, (QVariant)viewList[i]);
        ui->listViews->addItem(newItem);
    }    
    QPixmap pic(":/designer/fileicons/documents/"+QString(currentModel->getCurrentDoc()->metaObject()->className()).
                mid(0,QString(currentModel->getCurrentDoc()->metaObject()->className()).length()-3).toLower()+".png");
    if(!pic.isNull()){
        ui->labelImage->setPixmap(pic);
    }
    ui->labelFileSize->setText(QString::number(currentModel->getCurrentDoc()->getDocumentFileInfo().size()));
    ui->labelFileName->setText(currentModel->getCurrentDoc()->getDocumentFileInfo().fileName());
    ui->labelFilePath->setText(currentModel->getCurrentDoc()->getDocumentFileInfo().filePath());

    ui->labelFileType->setText(DesignerDocItf::getDocTypeTitle(currentModel->getCurrentDoc()->metaObject()->className()));

    connect(model, SIGNAL(storageUpdated()), SLOT(storageUpdated()));
}

FileDescriptionView::~FileDescriptionView()
{
    delete ui;
}

void FileDescriptionView::storageUpdated()
{
    if(currentModel->getCurrentDoc())
    {
        ui->labelFileName->setText(currentModel->getCurrentDoc()->getDocumentFileInfo().fileName());
    }
    else
        ui->labelFileName->setText(tr("<Not saved>"));
}

void FileDescriptionView::on_listViews_itemClicked(QListWidgetItem *item)
{
    mainWindow->createView(item->data(1).toString());
}
