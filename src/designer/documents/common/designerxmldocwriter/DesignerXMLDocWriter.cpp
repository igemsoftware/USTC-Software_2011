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

QDomDocument *DesignerXMLDocWriter::TravelRules(QDomElement rule_elem, QScriptValue script_value, QVector<int> &args)
{
    QScriptValue sub_script_value = script_value;
    if( rule_elem.hasAttribute("path") && !rule_elem.attribute("path").isEmpty() )
        sub_script_value = sub_script_value.property(rule_elem.attribute("path"));

    QDomDocument *doc = new QDomDocument;

    if( rule_elem.hasAttribute("condition") )
    {
        foreach( QString condition, rule_elem.attribute("condition").simplified().remove(" ").split(",") )
        {
            QString property = condition.split("=").at(0);
            QString value = condition.split("=").at(1);
            if( !sub_script_value.property(property).isValid()
                || !sub_script_value.property(property).toString() == value )
                return doc;
        }
    }

    QDomElement cur_elem;
    if( rule_elem.hasAttribute("target") )
    {
        delete doc;
        cur_elem = CreateDocByTarget(rule_elem, args, doc);
        if( rule_elem.hasAttribute("attribute") )
        {
            foreach( QString attribute, rule_elem.attribute("attribute").simplified().remove(" ").split(",") )
            {
                QString attribute_name = attribute.split(",").at(0);
                QString property_name = attribute.split(",").at(1);
                cur_elem.setAttribute(attribute_name, sub_script_value.property(property_name).toString());
            }
        }
    }

    if( rule_elem.tagName() == "object" )
    {
        for( QDomElement elem = rule_elem.firstChildElement() ; !elem.isNull() ; elem = elem.nextSiblingElement() )
            doc = MergeDocs(doc , TravelRules(elem, sub_script_value, args));
    }else if( rule_elem.tagName() == "array" )
    {
        QList<QScriptValue> value_list;
        qScriptValueToSequence(sub_script_value, value_list);

        int i = 0;
        foreach( QScriptValue value, value_list)
        {
            i++;
            args.push_back(i);
            for( QDomElement elem = rule_elem.firstChildElement() ; !elem.isNull() ; elem = elem.nextSiblingElement() )
            {
                doc = MergeDocs(doc , TravelRules(elem, value, args));
            }
            args.pop_back();
        }
    }

    return doc;
}

QDomElement DesignerXMLDocWriter::CreateDocByTarget(QString target, QVector<int> args, QDomDocument *&doc)
{

}

QDomDocument *DesignerXMLDocWriter::MergeDocs(QDomDocument *doc_1, QDomDocument *doc_2)
{
    MergeElements(doc_1->documentElement(), doc_2->documentElement());
    delete doc_2;
    return doc_1;
}

void DesignerXMLDocWriter::MergeElements(QDomDocument *doc)
{

}

QDomDocument *DesignerXMLDocWriter::WriteDoc(DesignerModelItf *model)
{
    QScriptValue root = model->getEngine()->globalObject();
    QDomDocument *doc = new QDomDocument;

    QVector<int> vec;
    for( QDomElement rule_elem = rule_xml.documentElement().firstChildElement() ; !rule_elem.isNull() ; rule_elem = rule_elem.nextSiblingElement() )
    {
        doc = MergeDoc(doc, travel(rule_elem, root, vec));
    }

    return doc;
}











