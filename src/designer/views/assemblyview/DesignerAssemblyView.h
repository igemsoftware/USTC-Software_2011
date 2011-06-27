#ifndef DESIGNERASSEMBLYVIEW_H
#define DESIGNERASSEMBLYVIEW_H

#include <QWidget>
#include <DesignerViewItf.h>

namespace Ui {
    class AssemblyView;
}

class AssemblyView : public DesignerViewItf
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit AssemblyView(QWidget *parent = 0);
    ~AssemblyView();

private:
    Ui::AssemblyView *ui;
};

#endif // DESIGNERASSEMBLYVIEW_H
