#ifndef DESIGNERXMLDOCPARSER_H
#define DESIGNERXMLDOCPARSER_H

#include <QtXml>
#include <QtScript>
#include "interfaces/DesignerModelItf.h"
#include "DesignerDebug.h"


class DesignerXMLDocParser
{
protected:
    DesignerXMLDocParser();

protected:
    struct parseTask
    {
        QDomElement taskElem;
        QScriptValue taskParent;
        size_t       taskHint;
        parseTask(QDomElement _elem, QScriptValue _parent, size_t _hint):taskElem(_elem), taskParent(_parent), taskHint(_hint){}
    };

protected:
    void appendValueToModel(QScriptValue value, QScriptValue root, QString path);
    void writeValueToModel(QScriptValue value, QScriptValue root, QString path);
    void writePropertyToModel(QScriptValue value, QScriptValue root, QString property);

public:
    static QString unmangleElementName(QString mangledName);
};

#endif // DESIGNERXMLDOCPARSER_H
