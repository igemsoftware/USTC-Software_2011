#ifndef NETWORKVIEW_H
#define NETWORKVIEW_H

#include <QtScript>
#include "interfaces/DesignerViewItf.h"

namespace Ui {
    class NetworkView;
}
class NetworkView : public DesignerViewItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit NetworkView(DesignerMainWnd *mainWnd, DesignerModelItf* model);
    ~NetworkView();
//protected:
//    QGraphicsView* graphicsView;
signals:
private:
    Ui::NetworkView *ui;
    QScriptEngine * engine;
public slots:
    void on_sceneSelectionChanged();
};

#endif // NETWORKVIEW_H
