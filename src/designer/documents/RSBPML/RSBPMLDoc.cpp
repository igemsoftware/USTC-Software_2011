#include <QtXml>
#include <QtScript>
#include "DesignerDebug.h"
#include "models/syntheticbiologicalpartmodel/SyntheticBiologicalPart.h"

#include "RSBPMLDoc.h"
#include "RSBPMLParser.h"

RSBPMLDoc::RSBPMLDoc()
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

DesignerModelComponent* RSBPMLDoc::loadFromFile(QFile& file, DesignerDocComponent* docComp)
{
    QDomDocument domdoc("rsbpmldoc");
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
    if(domDocElem.nodeName()!="rsbpml")
    {
        newModel->deleteLater();
        return NULL;
    }

    RSBPMLParser parser;

    bool retValue = parser.parse(newModel, domdoc);
    if(retValue)
    {
        newModel->requestUpdate(DesignerModelComponent::updateByData | DesignerModelComponent::updateByStorage);
    }
    return retValue ? newModel : NULL;
}

bool RSBPMLDoc::saveToFile(QFile& file, DesignerModelComponent* modelComp)
{
    return false;
}
