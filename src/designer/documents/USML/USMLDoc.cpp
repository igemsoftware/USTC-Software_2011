#include <QtXml>
#include <QtScript>

#include "USMLDoc.h"
#include "USMLParser.h"


USMLDoc::USMLDoc() :
    DesignerDocItf()
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

    currentModel = DesignerModelItf::createModel(domDocElem.attribute("model"), this);
    if(!currentModel)
        return false;

    USMLParser parser;

    bool retValue = parser.parse(currentModel, domdoc);
    if(retValue)
    {
        currentModel->requestUpdate(DesignerModelItf::updateByData | DesignerModelItf::updateByStorage);
    }
    return retValue;
}

bool USMLDoc::saveToFile(QFile& file)
{
    if(!file.open(QFile::ReadWrite))
        return false;

    QDomDocument usmlDoc("usml");
    usmlDoc.createDocumentFragment();

    QDomElement rootElem = usmlDoc.createElement("usml");
    rootElem.setTagName("usml");
    rootElem.setAttribute("model", getCurrentModel()->staticMetaObject.className());
    usmlDoc.appendChild(rootElem);

    typedef QPair<QDomElement, QScriptValue> workQueueRecord;
    QList<workQueueRecord> workQueue;
    workQueue.append(workQueueRecord(rootElem, getCurrentModel()->getModel()));
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
                QDomElement newNode = usmlDoc.createElement(iter.name());
                elem.appendChild(newNode);
                workQueue.append(workQueueRecord(newNode, iter.value()));
            }
            else
            {
                elem.setAttribute(iter.name(), iter.value().toString());
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

