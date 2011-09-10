#include <QtXml>
#include <QtScript>

#include "models/syntheticbiologicalpartmodel/SyntheticBiologicalPart.h"

#include "RSBPMLDoc.h"
#include "RSBPMLParser.h"

RSBPMLDoc::RSBPMLDoc() :
    DesignerDocComponent()
{
}

RSBPMLDoc::~RSBPMLDoc()
{

}

DesignerDocComponent::extentValue RSBPMLDoc::checkIfFileFitsDocumentType(QFile& file)
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
    currentModel = DesignerModelComponent::createModel(tr("SyntheticBiologicalPartModel"), this);
    if(!currentModel)
        return false;

    QDomElement domDocElem = domdoc.documentElement();
    if(domDocElem.nodeName()!="rsbpml")
    {
        currentModel->deleteLater();
        currentModel=NULL;
        return false;
    }

    RSBPMLParser parser;

    bool retValue = parser.parse(currentModel, domdoc);
    qDebug()<<currentModel->getEngine()->globalObject();
    if(retValue)
    {
        currentModel->requestUpdate(DesignerModelComponent::updateByData | DesignerModelComponent::updateByStorage);
    }
    return retValue;
}

bool RSBPMLDoc::saveToFile(QFile& file)
{
    return false;
}
