#ifndef DESIGNERASSEMBLYVIEW_H
#define DESIGNERASSEMBLYVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QToolBar>
#include <QToolButton>
#include <DesignerViewItf.h>
#include <views/assemblyview/AssemblyItemBrick.h>
#include <views/assemblyview/AssemblyItemCompartment.h>
#include <views/assemblyview/AssemblyItemPlasmid.h>
#include <views/assemblyview/AssemblyScene.h>

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

    QToolBar * recentModule;
    QTabWidget * toolBox;
    QGraphicsView * mainView;
    AssemblyScene * mainScene;
};

#endif // DESIGNERASSEMBLYVIEW_H
