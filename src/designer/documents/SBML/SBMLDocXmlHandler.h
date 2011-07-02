#ifndef SBMLDOCXMLHANDLER_H
#define SBMLDOCXMLHANDLER_H

#include <QXmlDefaultHandler>

class SBMLDocXmlHandler : public QXmlDefaultHandler
{
public:
    SBMLDocXmlHandler();

    bool startDocument();
    bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts);
    bool endElement(const QString& namespaceURI, const QString& localName, const QString& qName);

};

#endif // SBMLDOCXMLHANDLER_H
