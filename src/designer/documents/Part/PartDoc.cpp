#include <QtCore>
#include "PartDoc.h"
#include "PartDocParser.h"

#include "models/reactionnetworkmodel/ReactionNetwork.h"

PartDoc::PartDoc():
        DesignerDocItf()
    {

    }

PartDoc::~PartDoc()
{
    if(currentModel)
    {
        currentModel->deleteLater();
    }
}

bool PartDoc::loadFromFile(QFile& file)
{
    if(!file.open(QFile::ReadWrite|QIODevice::Text))
        if(!file.open(QFile::ReadOnly|QIODevice::Text))
            return false;

    QTextStream fin(&file);
    if(currentModel)
    {
        currentModel->deleteLater();
    }
    currentModel = DesignerModelItf::createModel(tr("ReactionNetworkModel"), this);
    if(!currentModel)
        return false;
    PartDocParser parser;
    bool status = parser.parse(*this, fin );
    file.close();
    return status;
}

bool PartDoc::saveToFile(QFile& file)
{
     return false;
}
PartDoc::extentValue PartDoc::checkIfFileFitsDocumentType( QFile& file )
{
    if(!file.open(QFile::ReadOnly))
        return NOTACCEPTABLE;

    file.close();
    if(!file.fileName().toLower().endsWith(".fasta"))
        return NOTACCEPTABLE;
    this->type="fasta";
    return EXACTLY;
}

PartDoc::extentValue PartDoc::checkIfDocCanConvertToThisType(QMetaObject& metaObject)
{
     return NOTACCEPTABLE;
}
