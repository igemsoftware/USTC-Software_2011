#include "DesignerDrawWnd.h"

DesignerDrawWnd::DesignerDrawWnd(QWidget *parent) :
    QDialog(parent)
{
    this->ddw=new DesignerDrawWidget(this);
    this->ddw->resize(800,600);
    this->ddw->installEventFilter(this);
    this->setWindowTitle(tr("DesignerDrawWindow"));
    this->resize(800,600);
}

bool DesignerDrawWnd::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==this->ddw && (event->type()==QEvent::MouseMove || event->type()==QEvent::MouseButtonRelease))
    {
        QMouseEvent * me=dynamic_cast<QMouseEvent *>(event);
        if(me->pos().x()<this->ddw->lastPoint.x())
            return true;
        else
            return false;
    }
    else
        return QWidget::eventFilter(obj,event);
}
