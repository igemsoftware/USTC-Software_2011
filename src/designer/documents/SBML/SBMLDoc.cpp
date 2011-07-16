#include <QtXml>
#include <QtScript>

#include "models/reactionnetworkmodel/ReactionNetwork.h"
#include "models/reactionnetworkmodel/ReactionNetworkSBMLImportProxy.h"

#include "SBMLDoc.h"
#include "SBMLDocParser.h"


SBMLDoc::SBMLDoc() :
    DesignerDocItf()
{

}

SBMLDoc::~SBMLDoc()
{
    if(currentModel)
    {
        currentModel->deleteLater();
    }
}

SBMLDoc::extentValue SBMLDoc::checkIfFileFitsDocumentType(QFile& file)
{
    QDomDocument domdoc("sbmldoctest");
    if(!file.open(QFile::ReadOnly))
        return NOTACCEPTABLE;
    if(!domdoc.setContent(&file))
    {
        file.close();
        return NOTACCEPTABLE;
    }
    file.close();

    QDomElement domDocElem = domdoc.documentElement();
    if(domDocElem.nodeName()==tr("sbml"))
        return EXACTLY;
    return NOTACCEPTABLE;
}

bool SBMLDoc::loadFromFile(QFile& file)
{
    QDomDocument domdoc("sbmldoctest");
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
    currentModel = DesignerModelItf::createModel(tr("ReactionNetworkModel"), this);
    if(!currentModel)
        return false;

    QDomElement domDocElem = domdoc.documentElement();
    if(domDocElem.nodeName()!="sbml")
    {
        currentModel->deleteLater();
        currentModel=NULL;
        return false;
    }

    SBMLDocParser parser;

    bool retValue = parser.parse(*currentModel, domDocElem);
    if(retValue)
    {
        currentModel->requestUpdate(DesignerModelItf::updateByData | DesignerModelItf::updateByStorage);
    }
    return retValue;
}

bool SBMLDoc::saveToFile(QFile& file)
{
    return false;
}

SBMLDoc::extentValue SBMLDoc::checkIfDocCanConvertToThisType(QMetaObject& metaObject)
{
    return SBMLDoc::NOTACCEPTABLE;
}

