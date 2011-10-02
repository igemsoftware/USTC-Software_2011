#include <QtXml>
#include <QtScript>

#include "USMLDoc.h"
#include "USMLParser.h"


USMLDoc::USMLDoc()
{

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

DesignerModelComponent* USMLDoc::loadFromFile(QFile& file, DesignerDocComponent* docComp)
{
    QDomDocument domdoc("usml");
    if(!file.open(QFile::ReadWrite))
        if(!file.open(QFile::ReadOnly))
            return NULL;

    if(!domdoc.setContent(&file))
    {
        file.close();
        return NULL;
    }
    file.close();

    QDomElement domDocElem = domdoc.documentElement();
    if(domDocElem.nodeName()!="usml"||domDocElem.attribute("model").isNull())
    {
        return NULL;
    }

    DesignerModelComponent* newModel = DesignerModelMgr::createModel(domDocElem.attribute("model"), docComp);
    if(!newModel)
        return NULL;

    USMLParser parser;

    bool retValue = parser.parse(newModel, domdoc);
    if(retValue)
    {
        newModel->requestUpdate(DesignerModelComponent::updateByData | DesignerModelComponent::updateByStorage);
        return newModel;
    }
    return NULL;
}

bool USMLDoc::saveToFile(QFile& file, DesignerModelComponent* modelComp)
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
    rootElem.setAttribute("model", modelComp->metaObject()->className());
    usmlDoc.appendChild(rootElem);

    QDomElement modelElem = usmlDoc.createElement("model");
    if(modelComp->getModel().isArray())
    {
        modelElem.setAttribute("_", "_");
    }
    rootElem.appendChild(modelElem);

    typedef QPair<QDomElement, QScriptValue> workQueueRecord;
    QList<workQueueRecord> workQueue;
    workQueue.append(workQueueRecord(modelElem, modelComp->getModel()));

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
