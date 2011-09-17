#ifndef WEBPAGEVIEW_H
#define WEBPAGEVIEW_H

#include "interfaces/DesignerViewItf.h"


class WebPageView : public DesignerViewComponent
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit WebPageView(DesignerMainWnd *mainWnd, DesignerModelComponent* model);

signals:

public slots:

};

#endif // WEBPAGEVIEW_H
