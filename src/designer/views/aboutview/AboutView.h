#ifndef ABOUTVIEW_H
#define ABOUTVIEW_H

#include "DesignerViewItf.h"

namespace Ui {
    class AboutView;
}

class AboutView : public DesignerViewItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit AboutView(DesignerMainWnd *mainWnd);
    ~AboutView();

signals:

public slots:

private slots:
    void on_closeButton_clicked();

private:
    Ui::AboutView *ui;

};

#endif // ABOUTVIEW_H
