#ifndef WEBPAGEVIEW_H
#define WEBPAGEVIEW_H

#include "interfaces/DesignerViewItf.h"


class WebPageView : public DesignerViewItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit WebPageView(DesignerMainWnd *mainWnd, DesignerModelItf* model);

signals:

public slots:

};

#endif // WEBPAGEVIEW_H
