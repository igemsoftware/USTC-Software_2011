#include <QtXml>
#include <QtScript>

#include "models/reactionnetworkmodel/ReactionNetwork.h"
#include "models/reactionnetworkmodel/ReactionNetworkSBMLImportProxy.h"

#include "SBMLDoc.h"
#include "SBMLDocParser.h"


SBMLDoc::SBMLDoc(DesignerMainWnd *parent) :
    DesignerDocItf(parent)
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
    currentModel = DesignerModelItf::createModel(tr("ReactionNetworkModel"));
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


    return parser.parse(*currentModel, domDocElem);
}

bool SBMLDoc::saveToFile(QFile& file)
{
    return false;
}

QList<QString> SBMLDoc::getSupportedViewList() const
{
    QList<QString> supportedViewList;
    supportedViewList.append("AssemblyView");
    supportedViewList.append("NetworkView");
    supportedViewList.append("BehaviorView");
    return supportedViewList;
}

SBMLDoc::extentValue SBMLDoc::checkIfDocCanConvertToThisType(QMetaObject& metaObject)
{
    return SBMLDoc::NOTACCEPTABLE;
}

