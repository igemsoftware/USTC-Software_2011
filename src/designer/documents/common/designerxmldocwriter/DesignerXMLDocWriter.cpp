#include "DesignerXMLDocWriter.h"
#include <QscriptEngine>


DesignerXMLDocWriter::DesignerXMLDocWriter(QString rule_file_name) :
    rule_xml("rule_xml")
{
    disabled = false;
    QFile fin(rule_file_name);
    if( !fin.open(QIODevice::ReadOnly) )
    {
        disabled = true;
        return;
    }
    if( !rule_xml.setContent(&fin) )
    {
        disabled = true;
        fin.close();
        return;
    }
    fin.close();
    return;
}


QDomDocument *DesignerXMLDocWriter::write(DesignerModelItf *model)
{
    model->getEngine()->globalObject()
}
