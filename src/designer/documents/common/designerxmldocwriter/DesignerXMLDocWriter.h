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
    QDomDocument *write( DesignerModelItf *model);

private:
    QDomDocument rule_xml;
    bool disabled;

    QDomDocument *TravelRules(QDomElement rule_elem, QScriptValue value, QVector<int> &args);
    QDomDocument *MergeDocs(QDomDocument *doc_1, QDomDocument *doc_2);
    QDomElement   CreateDocByTarget(QString target, QVector<int> args, QDomDocument *&doc);
    void          MergeElements(QDomDocument *doc);
};

#endif // DESIGNERXMLDOCWRITER_H
