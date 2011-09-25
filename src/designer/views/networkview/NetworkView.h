#ifndef NETWORKVIEW_H
#define NETWORKVIEW_H

#include <QtScript>
#include "interfaces/DesignerViewItf.h"
#include "NetworkViewGraphicsSceneNodeReaction.h"
#include "NetworkViewGraphicsSceneNodeSubstance.h"
#include "models/reactionnetworkmodel/ReactionNetwork.h"

class NetworkViewGraphicsScene;

namespace Ui {
    class NetworkView;
}
class NetworkView : public DesignerViewComponent
{
    Q_OBJECT
public:
    QPushButton *linebutton;
    QPushButton *modbutton;
    QString selectState;
    Q_INVOKABLE explicit NetworkView(DesignerMainWnd *mainWnd, DesignerModelComponent* model);
    ~NetworkView();

signals:

private:    
    NetworkViewGraphicsScene *NetworkGS;
    Ui::NetworkView *ui;
    QScriptEngine * engine;
public slots:
    void on_sceneSelectionChanged();
    void on_lineButtonClicked();
    void on_modButtonClicked();
    void refreshWidget();

    void on_invokeCopasi();

public:
    virtual void updateFeatureToolbar(QToolBar *toolBar);
};

#endif // NETWORKVIEW_H
