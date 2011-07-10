#include "MoDeLDoc.h"
#include <QTextStream>
#include <QtScript>

#include "models/reactionnetworkmodel/ReactionNetwork.h"
#include "models/reactionnetworkmodel/ReactionNetworkMoDeLImportProxy.h"

#include "MoDeLDoc.h"
#include "MoDeLDocParser.h"


MoDeLDoc::MoDeLDoc() :
    DesignerDocItf()
{

}

MoDeLDoc::~MoDeLDoc()
{
    if(currentModel)
    {
        currentModel->deleteLater();
    }
}

MoDeLDoc::extentValue MoDeLDoc::checkIfFileFitsDocumentType( QFile& file )
{
    if(!file.open(QFile::ReadOnly))
        return NOTACCEPTABLE;

    file.close();
    //fix later
    return EXACTLY;
}

bool MoDeLDoc::loadFromFile(QFile& file)
{
    if(!file.open(QFile::ReadOnly|QIODevice::Text))
        return false;

    QTextStream fin(&file);
    if(currentModel)
    {
        currentModel->deleteLater();
    }
    currentModel = DesignerModelItf::createModel(tr("ReactionNetworkModel"));
    if(!currentModel)
        return false;

    MoDeLDocParser parser;
    bool status = parser.parse(*currentModel, fin );
    file.close();
    return status;
}

bool MoDeLDoc::saveToFile(QFile& file)
{
    return false;
}

QList<QString> MoDeLDoc::getSupportedViewList() const
{
    QList<QString> supportedViewList;
    supportedViewList.append("AssemblyView");
    supportedViewList.append("NetworkView");
    supportedViewList.append("BehaviorView");
    return supportedViewList;
}

MoDeLDoc::extentValue MoDeLDoc::checkIfDocCanConvertToThisType(QMetaObject& metaObject)
{
    return MoDeLDoc::NOTACCEPTABLE;
}

