#ifndef DESIGNERXMLDOCWRITER_H
#define DESIGNERXMLDOCWRITER_H

#include <QtXml>
#include <QtScript>
#include <QMap>
#include "interfaces/DesignerModelItf.h"
#include "DesignerDebug.h"

class DesignerXMLDocWriter
{
public:
    DesignerXMLDocWriter(QString prototype_file_nae);
    QDomDocument *WriteDoc( DesignerModelComponent *model);

private:
    QDomDocument rule_xml;
    bool disabled;
    QDomDocument *doc;

    void TravelRules(const QDomElement &rule_elem, const QScriptValue &script_value, QVector<int> &args);
    QDomElement   CreateElemByTarget(const QString &target, QVector<int> args);
    void TrimTagName(QDomElement elem);
    void ConvertTextToElemAndInsert(const QString &text, QDomElement root);
    void PrependTagName(QDomElement elem);
};

#endif // DESIGNERXMLDOCWRITER_H
