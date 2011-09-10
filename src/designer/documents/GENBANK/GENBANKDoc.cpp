#include "GENBANKDocParser.h"
GENBANKDoc::GENBANKDoc():
        DesignerDocComponent()
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
    currentModel = DesignerModelComponent::createModel(tr("SyntheticBiologicalPartModel"), this);
    if(!currentModel)
        return false;
    GENBANKDocParser parser;

    bool status = parser.parse(currentModel,fin);
    file.close();
    return status;
}

bool GENBANKDoc::saveToFile(QFile& file)
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

GENBANKDoc::extentValue GENBANKDoc::checkIfFileFitsDocumentType( QFile& file )
{
    if(!file.open(QFile::ReadOnly))
        return NOTACCEPTABLE;
    QTextStream fin(&file);
    bool b=fin.readLine().toLower().startsWith("locus");
    file.close();
    if(b)
        return EXACTLY;
    return NOTACCEPTABLE;
}
