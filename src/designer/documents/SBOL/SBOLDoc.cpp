#include <QtXml>
#include <QtScript>

#include "models/syntheticbiologicalpartmodel/SyntheticBiologicalPart.h"

#include "SBOLDoc.h"
#include "SBOLParser.h"

SBOLDoc::SBOLDoc() :
    DesignerDocComponent()
{
}


SBOLDoc::~SBOLDoc()
{

}

DesignerDocComponent::extentValue SBOLDoc::checkIfFileFitsDocumentType(QFile& file)
{
    QDomDocument domdoc("sboldoc");
    if(!file.open(QFile::ReadOnly))
        return NOTACCEPTABLE;
    if(!domdoc.setContent(&file))
    {
        file.close();
        return NOTACCEPTABLE;
    }
    file.close();

    QDomElement domDocElem = domdoc.documentElement();
    if(domDocElem.nodeName()==tr("rdf:RDF"))
    {
        if(domDocElem.attribute("xmlns").endsWith("/sbol.owl#"))
            return EXACTLY;
        return DesignerDocComponent::INSUFFICIENTLY;
    }
    return NOTACCEPTABLE;
}

bool SBOLDoc::loadFromFile(QFile& file)
{
    QDomDocument domdoc("sboldoc");
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
    currentModel = DesignerModelMgr::createModel(tr("SyntheticBiologicalPartModel"), this);
    if(!currentModel)
        return false;

    QDomElement domDocElem = domdoc.documentElement();
    if(domDocElem.nodeName()!="rdf:RDF")
    {
        currentModel->deleteLater();
        currentModel=NULL;
        return false;
    }

    SBOLParser parser;

    bool retValue = parser.parse(currentModel, domdoc);
    qDebug()<<currentModel->getEngine()->globalObject();
    if(retValue)
    {
        currentModel->requestUpdate(DesignerModelComponent::updateByData | DesignerModelComponent::updateByStorage);
    }
    return retValue;
}

bool SBOLDoc::saveToFile(QFile& file)
{
    return false;
}
