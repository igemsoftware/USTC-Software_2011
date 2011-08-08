#ifndef ASSEMBLYVIEW_H
#define ASSEMBLYVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QToolBar>
#include <QToolButton>
#include "interfaces/DesignerViewItf.h"

#include "AssemblyItemPart.h"
#include "AssemblyItemCompartment.h"
#include "AssemblyItemPlasmid.h"
#include "AssemblyScene.h"
#include "AssemblyLib.h"
#include "AssemblyPropertyWidget.h"
#include "AssemblySearchWidget.h"

class AssemblyView : public DesignerViewItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit AssemblyView(DesignerMainWnd *mainWnd, DesignerModelItf* model);
    ~AssemblyView();

    QString outputMoDeLText();

private:

    QToolBar * recentModule;
    QTabWidget * toolBox;
    QGraphicsView * mainView;
    AssemblyScene * mainScene;
    AssemblyPropertyWidget * propertyWidget;
    AssemblySearchWidget * searchWidget;
    QScriptEngine * engine;
};

#endif // ASSEMBLYVIEW_H
