#include "EMBLDocParser.h"
EMBLDoc::EMBLDoc():
        DesignerDocComponent()
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
    currentModel = DesignerModelMgr::createModel(tr("SyntheticBiologicalPartModel"), this);
    if(!currentModel)
        return false;
    EMBLDocParser parser;

    bool status = parser.parse(currentModel,fin);
    file.close();
    return status;
}

bool EMBLDoc::saveToFile(QFile& file)
{
    if(!file.open(QFile::ReadWrite))
        return false;
    QTextStream stream(&file);
    for(int i=0;i<this->currentModel->getModel().property("length").toInt32();i++)
    {
        QScriptValue content;
        if(this->currentModel->getModel().property(i).property("*partsregistry.org*").property("newcontent").property("length").toInt32()==0)
            content=this->currentModel->getModel().property(i).property("*partsregistry.org*").property("content");
        else
            content=this->currentModel->getModel().property(i).property("*partsregistry.org*").property("newcontent");
        for(int j=0;j<content.property("length").toInt32();j++)
            stream<<content.property(j).toString()<<"\n";
    }
    file.close();
    return true;
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
