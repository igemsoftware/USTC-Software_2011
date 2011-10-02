#include "MoDeLDoc.h"
#include <QTextStream>
#include <QtScript>

#include "models/reactionnetworkmodel/ReactionNetwork.h"

#include "MoDeLDoc.h"
#include "MoDeLDocParser.h"
#include "views/assemblyview/AssemblyScene.h"


MoDeLDoc::MoDeLDoc()
{

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

DesignerModelComponent* MoDeLDoc::loadFromFile(QFile& file, DesignerDocComponent* docComp)
{
    if(!file.open(QFile::ReadWrite|QIODevice::Text))
        if(!file.open(QFile::ReadOnly|QIODevice::Text))
            return NULL;

    QTextStream fin(&file);

    DesignerModelComponent* newModel = DesignerModelMgr::createModel(tr("IGameModel"), docComp);
    if(!newModel)
        return NULL;

    MoDeLDocParser parser;
    bool status = parser.parse(*newModel, fin );
    file.close();
    return status ? newModel : NULL;
}

bool MoDeLDoc::saveToFile(QFile& file, DesignerModelComponent* modelComp)
{
    file.open(QFile::ReadWrite);
    QTextStream stream(&file);
    stream << AssemblyScene::outputMoDeLText(modelComp);
    stream.flush();
    return true;
}
