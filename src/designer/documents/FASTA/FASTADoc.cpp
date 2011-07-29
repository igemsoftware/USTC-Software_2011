#include "FASTADoc.h"
#include "FASTADocParser.h"
FASTADoc::FASTADoc():
        DesignerDocItf()
{

}
FASTADoc::~FASTADoc()
{
    if(currentModel)
    {
        currentModel->deleteLater();
    }
}
bool FASTADoc::loadFromFile(QFile& file)
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
    FASTADocParser parser;

    bool status = parser.parse(currentModel,fin);
    file.close();
    return status;
}

bool FASTADoc::saveToFile(QFile& file)
{
     return false;
}

FASTADoc::extentValue FASTADoc::checkIfFileFitsDocumentType( QFile& file )
{
    if(!file.open(QFile::ReadOnly))
        return NOTACCEPTABLE;
    QTextStream fin(&file);
    bool b=fin.readLine().startsWith(">");
    file.close();
    if(b)
        return EXACTLY;
    return NOTACCEPTABLE;
}
