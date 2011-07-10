#ifndef NETWORKVIEW_H
#define NETWORKVIEW_H

#include "DesignerViewItf.h"

class NetworkView : public DesignerViewItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit NetworkView(DesignerMainWnd *mainWnd);

signals:

public slots:

};

#endif // NETWORKVIEW_H
