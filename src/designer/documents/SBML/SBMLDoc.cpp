#include <QtXml>
#include <QtScript>

#include "models/reactionnetworkmodel/ReactionNetwork.h"

#include "SBMLDoc.h"
#include "SBMLParser.h"
#include "documents/common/designerxmldocwriter/DesignerXMLDocWriter.h"

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

DesignerModelComponent* SBMLDoc::loadFromFile(QFile& file, DesignerDocComponent* docComp)
{
    QDomDocument domdoc("sbmldoctest");
    if(!file.open(QFile::ReadWrite))
        if(!file.open(QFile::ReadOnly))
            return NULL;

    if(!domdoc.setContent(&file))
    {
        file.close();
        return NULL;
    }
    file.close();

    DesignerModelComponent* newModel = DesignerModelMgr::createModel(tr("ReactionNetworkModel"), docComp);
    if(!newModel)
        return NULL;

    QDomElement domDocElem = domdoc.documentElement();
    if(domDocElem.nodeName()!="sbml")
    {
        newModel->deleteLater();
        return NULL;
    }

    SBMLParser parser;

    bool retValue = parser.parse(newModel, domdoc);
    if(retValue)
    {
        newModel->requestUpdate(DesignerModelComponent::updateByData | DesignerModelComponent::updateByStorage);
    }
    return retValue ? newModel : NULL;
}

bool SBMLDoc::saveToFile(QFile& file, DesignerModelComponent* modelComp)
{
    DesignerXMLDocWriter writer(":/designer/documents/writerules/SBML.writerules");
    QDomDocument * doc = writer.WriteDoc(modelComp);
    file.open(QIODevice::ReadWrite);
    QTextStream stream(&file);
    stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" << doc->toString();
    stream.flush();
    return true;
}
