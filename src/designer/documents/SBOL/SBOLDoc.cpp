#include <QtXml>
#include <QtScript>

#include "models/syntheticbiologicalpartmodel/SyntheticBiologicalPart.h"

#include "SBOLDoc.h"
#include "SBOLParser.h"

SBOLDoc::SBOLDoc()
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
        return INSUFFICIENTLY;
    }
    return NOTACCEPTABLE;
}

DesignerModelComponent* SBOLDoc::loadFromFile(QFile& file, DesignerDocComponent* docComp)
{
    QDomDocument domdoc("sboldoc");
    if(!file.open(QFile::ReadWrite))
        if(!file.open(QFile::ReadOnly))
            return NULL;

    if(!domdoc.setContent(&file))
    {
        file.close();
        return NULL;
    }
    file.close();

    DesignerModelComponent* newModel = DesignerModelMgr::createModel(tr("SyntheticBiologicalPartModel"), docComp);
    if(!newModel)
        return NULL;

    QDomElement domDocElem = domdoc.documentElement();
    if(domDocElem.nodeName()!="rdf:RDF")
    {
        newModel->deleteLater();
        return false;
    }

    SBOLParser parser;

    bool retValue = parser.parse(newModel, domdoc);
    if(retValue)
    {
        newModel->requestUpdate(DesignerModelComponent::updateByData | DesignerModelComponent::updateByStorage);
    }
    return retValue ? newModel : NULL;
}

bool SBOLDoc::saveToFile(QFile& file, DesignerModelComponent* modelComp)
{
    return false;
}
