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
    //see if it is BIOMODELS.net :P
    if(model)
    {
        QXmlQuery query;
        QDomDocument domdoc("sbmldoctest");

        QBuffer device;
        device.setData(model->getEngine()->globalObject().property("*model*").property("*annotation*").toString().toUtf8());
        device.open(QIODevice::ReadOnly);

        query.bindVariable("rdfTree", &device);
        //query.setQuery("declare variable $name as xs:string := string($rdfTree/rdf:RDF/rdf:Description/bqmodel:is/rdf:Bag/rdf:li/@rdf:resource) \n $name");
        query.setQuery("doc($rdfTree)/rdf:RDF");

        QByteArray output;
        QBuffer buffer(&output);
        buffer.open(QIODevice::WriteOnly);

        QXmlFormatter formatter(query, &buffer);
        query.evaluateTo(&formatter);

        QMessageBox box;
        box.setText(QString::fromLatin1(output.constData()));
        box.exec();


    }
    if(!bHasHomePage)
        webView->setUrl(QUrl("http://2011.igem.org/Team:USTC-Software"));
}
