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

class AssemblyView : public DesignerViewComponent
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit AssemblyView(DesignerMainWnd *mainWnd, DesignerModelComponent* model);
    ~AssemblyView();

    QString outputMoDeLText();

    virtual void updateFeatureToolbar(QToolBar * toobar);
public slots:
    void igameDBRefresh();
    void CallIGame();

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
