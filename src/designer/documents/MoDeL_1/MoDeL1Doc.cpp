#include <QtXml>
#include <QtScript>

#include "models/reactionnetworkmodel/ReactionNetwork.h"

#include "MoDeL1Doc.h"
#include "MoDeL1Parser.h"


MoDeL1Doc::MoDeL1Doc() :
    DesignerDocComponent()
{

}

MoDeL1Doc::~MoDeL1Doc()
{
    if(currentModel)
    {
        currentModel->deleteLater();
    }
}

MoDeL1Doc::extentValue MoDeL1Doc::checkIfFileFitsDocumentType(QFile& file)
{
    QDomDocument domdoc("modeldoctest");
    if(!file.open(QFile::ReadOnly))
        return NOTACCEPTABLE;
    if(!domdoc.setContent(&file))
    {
        file.close();
        return NOTACCEPTABLE;
    }
    file.close();

    QDomElement domDocElem = domdoc.documentElement();
    if(domDocElem.nodeName()==tr("MoDeL"))
        return EXACTLY;
    return NOTACCEPTABLE;
}

bool MoDeL1Doc::loadFromFile(QFile& file)
{
    QDomDocument domdoc("modeldoctest");
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
    currentModel = DesignerModelMgr::createModel(tr("ReactionNetworkModel"), this);
    if(!currentModel)
        return false;

    QDomElement domDocElem = domdoc.documentElement();
    if(domDocElem.nodeName()!="MoDeL")
    {
        currentModel->deleteLater();
        currentModel=NULL;
        return false;
    }

    MoDeL1Parser parser;

    bool retValue = parser.parse(currentModel, domdoc);
    if(retValue)
    {
        currentModel->requestUpdate(DesignerModelComponent::updateByData | DesignerModelComponent::updateByStorage);
    }
    return retValue;
}

bool MoDeL1Doc::saveToFile(QFile& file)
{
    return false;
}

MoDeL1Doc::extentValue MoDeL1Doc::checkIfDocCanConvertToThisType(QMetaObject& metaObject)
{
    return MoDeL1Doc::NOTACCEPTABLE;
}

