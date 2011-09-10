#include <QtXml>
#include <QtScript>

#include "models/reactionnetworkmodel/ReactionNetwork.h"

#include "SBMLDoc.h"
#include "SBMLParser.h"
#include "documents/common/designerxmldocwriter/DesignerXMLDocWriter.h"


SBMLDoc::SBMLDoc() :
    DesignerDocComponent()
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
    currentModel = DesignerModelComponent::createModel(tr("ReactionNetworkModel"), this);
    if(!currentModel)
        return false;

    QDomElement domDocElem = domdoc.documentElement();
    if(domDocElem.nodeName()!="sbml")
    {
        currentModel->deleteLater();
        currentModel=NULL;
        return false;
    }

    SBMLParser parser;

    bool retValue = parser.parse(currentModel, domdoc);
    if(retValue)
    {
        currentModel->requestUpdate(DesignerModelComponent::updateByData | DesignerModelComponent::updateByStorage);
    }
    return retValue;
}

bool SBMLDoc::saveToFile(QFile& file)
{
    DesignerXMLDocWriter writer("D:\\iGame\\GIT\\lachesis\\src\\designer\\documents\\SBML\\SBML.writerules");
    QDomDocument * doc = writer.WriteDoc(getCurrentModel());
    file.open(QIODevice::ReadWrite);
    QTextStream stream(&file);
    stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" << doc->toString();
    stream.flush();
    return true;
}

SBMLDoc::extentValue SBMLDoc::checkIfDocCanConvertToThisType(QMetaObject& metaObject)
{
    return SBMLDoc::NOTACCEPTABLE;
}

