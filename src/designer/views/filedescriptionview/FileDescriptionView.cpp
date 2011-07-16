#include "FileDescriptionView.h"
#include "ui_FileDescriptionView.h"

#include "DesignerMainWnd.h"

#include "interfaces/DesignerInterface.h"

FileDescriptionView::FileDescriptionView(DesignerMainWnd* mainWnd) :
    DesignerViewItf(mainWnd),
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
}

FileDescriptionView::~FileDescriptionView()
{
    delete ui;
}

void FileDescriptionView::on_listViews_itemClicked(QListWidgetItem *item)
{
    mainWindow->createView(item->data(1).toString());
}
