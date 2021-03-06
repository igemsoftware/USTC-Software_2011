#ifndef ABOUTVIEW_H
#define ABOUTVIEW_H

#include "interfaces/DesignerViewItf.h"

namespace Ui {
    class AboutView;
}

class AboutView : public DesignerViewComponent
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit AboutView(DesignerMainWnd *mainWnd, DesignerModelComponent* model);
    ~AboutView();

signals:

public slots:

private slots:
    void on_closeButton_clicked();

private:
    Ui::AboutView *ui;

};

#endif // ABOUTVIEW_H
