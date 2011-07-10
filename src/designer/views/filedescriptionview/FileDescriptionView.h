#ifndef FILEDESCRIPTIONVIEW_H
#define FILEDESCRIPTIONVIEW_H

#include "DesignerViewItf.h"

namespace Ui {
    class FileDescriptionView;
}

class FileDescriptionView : public DesignerViewItf
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit FileDescriptionView(DesignerMainWnd* mainWnd);
    ~FileDescriptionView();

public:

private slots:
    void on_listViews_itemClicked(QListWidgetItem *item);

private:
    Ui::FileDescriptionView *ui;
};

#endif // FILEDESCRIPTIONVIEW_H
