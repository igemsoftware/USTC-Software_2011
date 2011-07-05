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
#include "AssemblyItemPart.h"
#include "AssemblyItemCompartment.h"
#include "AssemblyItemPlasmid.h"
#include "AssemblyScene.h"
#include "AssemblyLib.h"
#include "AssemblyPropertyWidget.h"
#include "AssemblySearchWidget.h"

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
    AssemblyPropertyWidget * propertyWidget;
    AssemblySearchWidget * searchWidget;
};

#endif // DESIGNERASSEMBLYVIEW_H
