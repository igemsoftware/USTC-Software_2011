#ifndef ODEVIEW_H
#define ODEVIEW_H

#include "interfaces/DesignerViewItf.h"

class QtMmlWidget;

class ODEView : public DesignerViewItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ODEView(DesignerMainWnd *mainWnd, DesignerModelItf* model);

    void resizeEvent ( QResizeEvent * event );

    QtMmlWidget * mmlWidget;
    QTextEdit   * textWidget;
signals:

public slots:
    void textChanged();

};

#endif // ODEVIEW_H
