#ifndef FILEDESCRIPTIONVIEW_H
#define FILEDESCRIPTIONVIEW_H

#include "interfaces/DesignerViewItf.h"

namespace Ui {
    class FileDescriptionView;
}

class FileDescriptionView : public DesignerViewComponent
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit FileDescriptionView(DesignerMainWnd* mainWnd, DesignerModelComponent* model);
    ~FileDescriptionView();

public slots:
    void storageUpdated();
//public slots:

private slots:
    void on_listViews_itemClicked(QListWidgetItem *item);

private:
    Ui::FileDescriptionView *ui;
};

#endif // FILEDESCRIPTIONVIEW_H
