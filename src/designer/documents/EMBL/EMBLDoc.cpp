#include "EMBLDocParser.h"
EMBLDoc::EMBLDoc():
        DesignerDocItf()
{

}
EMBLDoc::~EMBLDoc()
{
    if(currentModel)
    {
        currentModel->deleteLater();
    }
}
bool EMBLDoc::loadFromFile(QFile& file)
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
    EMBLDocParser parser;

    bool status = parser.parse(currentModel,fin);
    file.close();
    return status;
}

bool EMBLDoc::saveToFile(QFile& file)
{
     return false;
}

EMBLDoc::extentValue EMBLDoc::checkIfFileFitsDocumentType( QFile& file )
{
    if(!file.open(QFile::ReadOnly))
        return NOTACCEPTABLE;
    QTextStream fin(&file);
    bool b=fin.readLine().toLower().startsWith("id");
    file.close();
    if(b)
        return EXACTLY;
    return NOTACCEPTABLE;
}
