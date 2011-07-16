#ifndef PARTVIEW_H
#define PARTVIEW_H

#include "DesignerViewItf.h"

namespace Ui {
    class PartView;
}

class PartView : public DesignerViewItf
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit PartView(DesignerMainWnd *mainWnd);
    ~PartView();

private:
    Ui::PartView *ui;
};

#endif // PARTVIEW_H
