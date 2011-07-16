#ifndef NETWORKVIEW_H
#define NETWORKVIEW_H

#include <QtScript>
#include "interfaces/DesignerViewItf.h"

class NetworkView : public DesignerViewItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit NetworkView(DesignerMainWnd *mainWnd);

protected:
    QGraphicsView* graphicsView;

signals:
    void updateSelectedItem(QScriptValue);

public slots:
    void on_sceneSelectionChanged();
};

#endif // NETWORKVIEW_H
