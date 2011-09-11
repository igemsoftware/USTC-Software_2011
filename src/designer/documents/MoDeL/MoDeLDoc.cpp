#include "MoDeLDoc.h"
#include <QTextStream>
#include <QtScript>

#include "models/reactionnetworkmodel/ReactionNetwork.h"

#include "MoDeLDoc.h"
#include "MoDeLDocParser.h"


MoDeLDoc::MoDeLDoc() :
    DesignerDocComponent()
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
    if(!file.fileName().toLower().endsWith(".model"))
        return NOTACCEPTABLE;

    // A quick workaround : Or the system will be unusable -by CrLF0710.

    return EXACTLY;
}

bool MoDeLDoc::loadFromFile(QFile& file)
{
    if(!file.open(QFile::ReadWrite|QIODevice::Text))
        if(!file.open(QFile::ReadOnly|QIODevice::Text))
            return false;

    QTextStream fin(&file);
    if(currentModel)
    {
        currentModel->deleteLater();
    }
    currentModel = DesignerModelMgr::createModel(tr("IGameModel"),this);
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
    return supportedViewList;
}

MoDeLDoc::extentValue MoDeLDoc::checkIfDocCanConvertToThisType(QMetaObject& metaObject)
{
    return MoDeLDoc::NOTACCEPTABLE;
}

