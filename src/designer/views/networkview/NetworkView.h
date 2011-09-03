#ifndef NETWORKVIEW_H
#define NETWORKVIEW_H

#include <QtScript>
#include "interfaces/DesignerViewItf.h"
#include "NetworkViewGraphicsSceneNodeReaction.h"
#include "NetworkViewGraphicsSceneNodeSubstance.h"

namespace Ui {
    class NetworkView;
}
class NetworkView : public DesignerViewItf
{
    Q_OBJECT
public:
    QPushButton *linebutton;
    Q_INVOKABLE explicit NetworkView(DesignerMainWnd *mainWnd, DesignerModelItf* model);
    ~NetworkView();
//protected:
//    QGraphicsView* graphicsView;
signals:

private:
    QString selectState;
    NetworkViewGraphicsSceneNodeReaction *reaction;
    NetworkViewGraphicsSceneNodeSubstance *substance;
    Ui::NetworkView *ui;
    QScriptEngine * engine;
public slots:
    void on_sceneSelectionChanged();
    void on_lineButtonClicked();
};

#endif // NETWORKVIEW_H
