#include <QtXmlPatterns/QXmlQuery>
#include <QtXmlPatterns/QXmlFormatter>
#include <QDomElement>
#include <QtGui>
#include <QtWebKit>
#include "WebPageView.h"
#include "interfaces/DesignerModelItf.h"

WebPageView::WebPageView(DesignerMainWnd* mainWnd, DesignerModelComponent *model) :
    DesignerViewComponent(mainWnd, model)
{
    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    QWebView* webView = new QWebView(this);
    gridLayout->addWidget(webView, 0, 0, 0, 1);

    webView->show();

    bool bHasHomePage = false;

    if(!bHasHomePage)
        webView->setUrl(QUrl("http://2011.igem.org/Team:USTC-Software"));
}
