#ifndef DESIGNERDRAWWND_H
#define DESIGNERDRAWWND_H

#include "DesignerDrawWidget.h"

class DesignerDrawWnd : public QDialog
{
    Q_OBJECT
public:
    DesignerDrawWidget *ddw;
    explicit DesignerDrawWnd(QWidget *parent = 0);
    bool eventFilter(QObject *obj, QEvent *event);
signals:

public slots:

};

#endif // DESIGNERDRAWWND_H
