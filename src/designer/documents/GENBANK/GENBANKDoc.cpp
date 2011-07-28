#include "GENBANKDocParser.h"
GENBANKDoc::GENBANKDoc():
        DesignerDocItf()
{

}
GENBANKDoc::~GENBANKDoc()
{
    if(currentModel)
    {
        currentModel->deleteLater();
    }
}
bool GENBANKDoc::loadFromFile(QFile& file)
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
    GENBANKDocParser parser;

    bool status = parser.parse(currentModel,fin);
    file.close();
    return status;
}

bool GENBANKDoc::saveToFile(QFile& file)
{
     return false;
}

GENBANKDoc::extentValue GENBANKDoc::checkIfFileFitsDocumentType( QFile& file )
{
    if(!file.open(QFile::ReadOnly))
        return NOTACCEPTABLE;

    file.close();
    if(file.fileName().toLower().endsWith(".genbank"))
        return EXACTLY;
    return NOTACCEPTABLE;
}
