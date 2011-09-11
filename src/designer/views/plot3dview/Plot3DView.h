#ifndef PLOT3DVIEW_H
#define PLOT3DVIEW_H

#include "interfaces/DesignerViewItf.h"

class Plot;

class Plot3DView : public DesignerViewComponent
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit Plot3DView(DesignerMainWnd *mainWnd, DesignerModelComponent* model);
    Plot* plot;

protected:
    virtual void resizeEvent ( QResizeEvent * event );

signals:

public slots:

};

#endif // PLOT3DVIEW_H
