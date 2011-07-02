#include <QtXml>
#include <QtScript>

#include "SBMLDoc.h"
#include "SBMLDocXmlHandler.h"

#include "models/reactionnetworkmodel/ReactionNetwork.h"

SBMLDoc::SBMLDoc(QObject *parent) :
    DesignerDocItf(parent),
    currentModel(NULL)
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
    currentModel = DesignerModelItf::createModel(tr("ReactionNetwork"));





    QDomElement domDocElem = domdoc.documentElement();
    if(domDocElem.nodeName()==tr("sbml"))
        ;


    //qScriptValueFromSequence
/*
    QXmlInputSource inputSource(&file);

    QXmlSimpleReader reader;

    SBMLDocXmlHandler handler;
    reader.setContentHandler(&handler);

    reader.parse(&inputSource);
*/

    return false;
}

bool SBMLDoc::saveToFile(QFile& file)
{
    return false;
}

SBMLDoc::extentValue SBMLDoc::checkIfDocCanConvertToThisType(QMetaObject& metaObject)
{
    return SBMLDoc::NOTACCEPTABLE;
}

