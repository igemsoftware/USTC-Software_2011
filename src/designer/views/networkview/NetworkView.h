#ifndef NETWORKVIEW_H
#define NETWORKVIEW_H

#include <QtScript>
#include "interfaces/DesignerViewItf.h"
#include "NetworkViewGraphicsSceneNodeReaction.h"
#include "NetworkViewGraphicsSceneNodeSubstance.h"
#include "models/reactionnetworkmodel/ReactionNetwork.h"

namespace Ui {
    class NetworkView;
}
class NetworkView : public DesignerViewItf
{
    Q_OBJECT
public:
    QPushButton *linebutton;
    QPushButton *modbutton;
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
    void on_modButtonClicked();
};

#endif // NETWORKVIEW_H
