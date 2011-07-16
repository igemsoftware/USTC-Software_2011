#include "FileDescriptionView.h"
#include "ui_FileDescriptionView.h"

#include "DesignerMainWnd.h"

LACHESIS_DECLARE_VIEW(FileDescriptionView, "Views");

FileDescriptionView::FileDescriptionView(DesignerMainWnd* mainWnd) :
    DesignerViewItf(mainWnd),
    ui(new Ui::FileDescriptionView)
{
    ui->setupUi(this);

    QList<QString> viewList = mainWnd->getCurrentDoc("")->getSupportedViewList();
    for(int i=0;i<viewList.count();i++)
    {
        QListWidgetItem *newItem = new QListWidgetItem(DesignerViewItf::getViewTitleByName(viewList[i]));
        newItem->setData(1, (QVariant)viewList[i]);
        ui->listViews->addItem(newItem);
    }
}

FileDescriptionView::~FileDescriptionView()
{
    delete ui;
}

void FileDescriptionView::on_listViews_itemClicked(QListWidgetItem *item)
{
    mainWindow->createView(item->data(1).toString());
}
