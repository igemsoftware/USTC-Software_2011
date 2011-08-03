#ifndef NETWORKVIEW_H
#define NETWORKVIEW_H

#include <QtScript>
#include "interfaces/DesignerViewItf.h"

class NetworkView : public DesignerViewItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit NetworkView(DesignerMainWnd *mainWnd, DesignerModelItf* model);

protected:
    QGraphicsView* graphicsView;

signals:

public slots:
    void on_sceneSelectionChanged();
};

#endif // NETWORKVIEW_H
