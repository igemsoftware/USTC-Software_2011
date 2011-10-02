#include <QtXml>
#include <QtScript>

#include "models/reactionnetworkmodel/ReactionNetwork.h"

#include "MoDeL1Doc.h"
#include "MoDeL1Parser.h"


MoDeL1Doc::MoDeL1Doc()
{

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

DesignerModelComponent* MoDeL1Doc::loadFromFile(QFile& file, DesignerDocComponent* docComp)
{
    QDomDocument domdoc("modeldoctest");
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
    if(domDocElem.nodeName()!="MoDeL")
    {
        newModel->deleteLater();
        return NULL;
    }

    MoDeL1Parser parser;

    bool retValue = parser.parse(newModel, domdoc);
    if(retValue)
    {
        newModel->requestUpdate(DesignerModelComponent::updateByData | DesignerModelComponent::updateByStorage);
    }
    return retValue ? newModel : NULL;
}

bool MoDeL1Doc::saveToFile(QFile& file, DesignerModelComponent* modelComp)
{
    return false;
}
