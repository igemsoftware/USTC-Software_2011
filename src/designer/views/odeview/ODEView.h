#ifndef ODEVIEW_H
#define ODEVIEW_H

#include "DesignerViewItf.h"

class ODEView : public DesignerViewItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ODEView(DesignerMainWnd *mainWnd);

signals:

public slots:

};

#endif // ODEVIEW_H
