#include <QtXml>
#include <QtScript>

#include "USMLDoc.h"
#include "USMLParser.h"


USMLDoc::USMLDoc() :
    DesignerDocComponent()
{

}

USMLDoc::~USMLDoc()
{
    if(currentModel)
    {
        currentModel->deleteLater();
    }
}

USMLDoc::extentValue USMLDoc::checkIfFileFitsDocumentType(QFile& file)
{
    QDomDocument domdoc("usml");
    if(!file.open(QFile::ReadOnly))
        return NOTACCEPTABLE;
    if(!domdoc.setContent(&file))
    {
        file.close();
        return NOTACCEPTABLE;
    }
    file.close();

    QDomElement domDocElem = domdoc.documentElement();
    if(domDocElem.nodeName()==tr("usml"))
        return EXACTLY;
    return NOTACCEPTABLE;
}

bool USMLDoc::loadFromFile(QFile& file)
{
    QDomDocument domdoc("usml");
    if(!file.open(QFile::ReadWrite))
        if(!file.open(QFile::ReadOnly))
            return false;

    if(!domdoc.setContent(&file))
    {
        file.close();
        return NOTACCEPTABLE;
    }
    file.close();

    if(currentModel)
    {
        currentModel->deleteLater();
        currentModel = NULL;
    }

    QDomElement domDocElem = domdoc.documentElement();
    if(domDocElem.nodeName()!="usml"||domDocElem.attribute("model").isNull())
    {
        return false;
    }

    currentModel = DesignerModelMgr::createModel(domDocElem.attribute("model"), this);
    if(!currentModel)
        return false;

    USMLParser parser;

    bool retValue = parser.parse(currentModel, domdoc);
    if(retValue)
    {
        currentModel->requestUpdate(DesignerModelComponent::updateByData | DesignerModelComponent::updateByStorage);
    }
    return retValue;
}

bool USMLDoc::saveToFile(QFile& file)
{
    struct mangler
    {
        static QString nameMangle(QString text)
        {
            QString retText;
            for(int i = 0; i < text.length(); i++)
            {
                if(((QChar)text[i]).isLetter())
                {
                    retText+=text[i];
                }
                else
                {
                    retText+="_";
                    retText+=QString::number(text[i].unicode(),16);
                    retText+="_";
                }
            }
            return retText;
        }
    };

    if(!file.open(QFile::ReadWrite))
        return false;

    QDomDocument usmlDoc("usml");
    usmlDoc.createDocumentFragment();

    QDomElement rootElem = usmlDoc.createElement("usml");
    rootElem.setAttribute("model", getCurrentModel()->metaObject()->className());
    usmlDoc.appendChild(rootElem);

    QDomElement modelElem = usmlDoc.createElement("model");
    if(getCurrentModel()->getModel().isArray())
    {
        modelElem.setAttribute("_", "_");
    }
    rootElem.appendChild(modelElem);

    typedef QPair<QDomElement, QScriptValue> workQueueRecord;
    QList<workQueueRecord> workQueue;
    workQueue.append(workQueueRecord(modelElem, getCurrentModel()->getModel()));
    int workQueuePos = 0;
    while(workQueuePos < workQueue.size())
    {
        workQueueRecord& curItem = workQueue[workQueuePos];
        QDomElement& elem = curItem.first;


        QScriptValueIterator iter(curItem.second);
        while(iter.hasNext())
        {
            iter.next();
            if(iter.value().isObject()/*||iter.value().isArray()*/)
            {
                QDomElement newNode = usmlDoc.createElement(mangler::nameMangle(iter.name()));
                if(iter.value().isArray())
                {
                    newNode.setAttribute("_", "_");
                }
                elem.appendChild(newNode);
                workQueue.append(workQueueRecord(newNode, iter.value()));
            }
            else
            {
                elem.setAttribute(mangler::nameMangle(iter.name()), iter.value().toString());
            }
        }
        workQueuePos++;
    }

    QTextStream ts(&file);
    usmlDoc.save(ts, 4);


    file.close();

    return true;
}

USMLDoc::extentValue USMLDoc::checkIfDocCanConvertToThisType(QMetaObject& metaObject)
{
    return USMLDoc::NOTACCEPTABLE;
}

