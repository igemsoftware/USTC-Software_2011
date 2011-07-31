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
    QDomDocument domdoc("usmldoctest");
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
    QDomDocument domdoc("usmldoctest");
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
    return false;
}

USMLDoc::extentValue USMLDoc::checkIfDocCanConvertToThisType(QMetaObject& metaObject)
{
    return USMLDoc::NOTACCEPTABLE;
}

