#include <QtXml>
#include <QtScript>

#include "RSBPMLDoc.h"
#include "RSBPMLDocParser.h"
#include "models/syntheticbiologicalpartmodel/SyntheticBiologicalPart.h"

RSBPMLDoc::RSBPMLDoc() :
    DesignerDocItf()
{
}

RSBPMLDoc::~RSBPMLDoc()
{

}

DesignerDocItf::extentValue RSBPMLDoc::checkIfFileFitsDocumentType(QFile& file)
{
    QDomDocument domdoc("rsbpmldoc");
    if(!file.open(QFile::ReadOnly))
        return NOTACCEPTABLE;
    if(!domdoc.setContent(&file))
    {
        file.close();
        return NOTACCEPTABLE;
    }
    file.close();

    QDomElement domDocElem = domdoc.documentElement();
    if(domDocElem.nodeName()==tr("rsbpml"))
        return EXACTLY;
    return NOTACCEPTABLE;
}

bool RSBPMLDoc::loadFromFile(QFile& file)
{
    QDomDocument domdoc("rsbpmldoc");
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
    }
    currentModel = DesignerModelItf::createModel(tr("SyntheticBiologicalPartModel"), this);
    if(!currentModel)
        return false;

    QDomElement domDocElem = domdoc.documentElement();
    if(domDocElem.nodeName()!="rsbpml")
    {
        currentModel->deleteLater();
        currentModel=NULL;
        return false;
    }

    RSBPMLDocParser parser;

    bool retValue = parser.parse(*currentModel, domDocElem);
    if(retValue)
    {
        currentModel->requestUpdate(DesignerModelItf::updateByData | DesignerModelItf::updateByStorage);
    }
    return retValue;
}

bool RSBPMLDoc::saveToFile(QFile& file)
{
    return false;
}
