#include <QtCore>
#include "PartDoc.h"
#include "PartDocParser.h"

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
    currentModel = DesignerModelItf::createModel(tr("SyntheticBiologicalPartModel"), this);
    if(!currentModel)
        return false;
    PartDocParser parser;
    this->detectDocType(file);

    bool status = parser.parse(currentModel,fin,this->type);
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
    //detect doc type;
    return INSUFFICIENTLY;
}

void PartDoc::detectDocType(QFile &file)
{
    if(file.fileName().endsWith(".fasta"))
        this->type="fasta";
}

