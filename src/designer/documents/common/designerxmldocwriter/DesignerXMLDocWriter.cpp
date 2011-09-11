#include "DesignerXMLDocWriter.h"
#include <QScriptEngine>
#include "models/common/ModelSymbol.h"
#include "DesignerDebug.h"


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

void DesignerXMLDocWriter::TravelRules(const QDomElement &rule_elem, const QScriptValue &script_value, QVector<int> &args)
{
    qDebug() << rule_elem.tagName();
    QScriptValue sub_script_value = script_value;
    if( rule_elem.hasAttribute("path") && !rule_elem.attribute("path").isEmpty() )
    {
        qDebug() << "cd:" << rule_elem.attribute("path");
        sub_script_value = sub_script_value.property(rule_elem.attribute("path"));
    }

    if( rule_elem.hasAttribute("condition") )
    {
        foreach( QString condition, rule_elem.attribute("condition").simplified().remove(" ").split(",") )
        {
            QString property = condition.split("=").at(0);
            QString value = condition.split("=").at(1);
            if( !sub_script_value.property(property).isValid()
                || sub_script_value.property(property).toString() != value )
                return;
        }
    }

    QDomElement cur_elem;
    if( rule_elem.hasAttribute("target") )
    {
        qDebug() << "target:" << rule_elem.attribute("target");
        cur_elem = CreateElemByTarget(rule_elem.attribute("target"), args);
        if( rule_elem.hasAttribute("attribute") )
        {
            foreach( QString attribute, rule_elem.attribute("attribute").simplified().remove(" ").split(",") )
            {
                QString attribute_name = attribute.split("=").at(0);
                QString property_name = attribute.split("=").at(1);
                if( !sub_script_value.property(property_name).isValid() ) continue;
                if( attribute_name == "$CHILD" )
                {
                    ConvertTextToElemAndInsert(sub_script_value.property(property_name).toString(), cur_elem);
                }else{
                    cur_elem.setAttribute(attribute_name, sub_script_value.property(property_name).toString());
                }
            }
        }
    }

    if( rule_elem.tagName() == "object" )
    {
        for( QDomElement elem = rule_elem.firstChildElement() ; !elem.isNull() ; elem = elem.nextSiblingElement() )
            TravelRules(elem, sub_script_value, args);
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
                TravelRules(elem, value, args);
            }
            args.pop_back();
        }
    }

    return;
}

QDomElement DesignerXMLDocWriter::CreateElemByTarget(const QString &target, QVector<int> args)
{
    QRegExp rx("^(\\w+)(\\(([^\\)]+)\\))?$");
    QDomElement elem;
    int depth = 0;
    foreach( QString tag_name, target.simplified().remove(" ").split("/") )
    {
        depth++;

        qDebug() << rx.indexIn(tag_name);
        qDebug() << rx.cap(1) << "\n" << rx.cap(3);
        tag_name = "";
        int i = 0;
        foreach( QString arg, rx.cap(3).split("$", QString::SkipEmptyParts) )
        {
            i++;
            tag_name += QObject::tr("_") + args.at(arg.toInt()-1) + "_";
        }
        tag_name = QString("_%1_").arg(i) + tag_name + rx.cap(1);
        if( depth == 1 )
        {
            elem = doc->documentElement();
            if( elem.isNull() || elem.tagName() != tag_name )
            {
                doc->appendChild( doc->createElement(tag_name) );
                elem = doc->documentElement();
            }
        }else{
            if( elem.firstChildElement(tag_name).isNull() )
            {
                elem.appendChild( doc->createElement(tag_name) );
            }
            elem = elem.firstChildElement(tag_name);
        }

    }
    return elem;
}


void DesignerXMLDocWriter::TrimTagName(QDomElement elem)
{
    QRegExp rx("^_(\\d+)_");
    QString tag_name = elem.tagName();
    if( !tag_name.isNull() )
    {
        rx.indexIn(tag_name);
        tag_name = tag_name.mid((rx.cap(1).toInt()+1)*3 , -1);
        elem.setTagName(tag_name);
    }
    for( QDomElement sub_elem = elem.firstChildElement() ; !sub_elem.isNull() ; sub_elem = sub_elem.nextSiblingElement() )
    {
        TrimTagName(sub_elem);
    }
}

void DesignerXMLDocWriter::ConvertTextToElemAndInsert(const QString &text, QDomElement root)
{
    QDomDocument tmp_doc;
    tmp_doc.setContent(text);
    QDomElement child = tmp_doc.documentElement();
    PrependTagName(child);
    root.appendChild( doc->importNode(child,true) );
    return;
}

void DesignerXMLDocWriter::PrependTagName(QDomElement elem)
{
    QString tag_name = elem.tagName();
    if( !tag_name.isNull() )
    {
        tag_name = QObject::tr("_0_") + tag_name;
        elem.setTagName(tag_name);
    }
    for( QDomElement sub_elem = elem.firstChildElement() ; !sub_elem.isNull() ; sub_elem = sub_elem.nextSiblingElement() )
    {
        PrependTagName(sub_elem);
    }
}

QDomDocument *DesignerXMLDocWriter::WriteDoc(DesignerModelComponent *model)
{
    if( disabled )
    {
        qDebug() << "Writer Disabled";
        return 0;
    }
    QScriptValue root = model->getEngine()->globalObject();
    doc = new QDomDocument;

    QVector<int> args;

    qDebug() << rule_xml.documentElement().tagName();
    TravelRules(rule_xml.documentElement(), root, args);

    TrimTagName(doc->documentElement());
    return doc;
}











