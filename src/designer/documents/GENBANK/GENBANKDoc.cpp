#include "GENBANKDocParser.h"

GENBANKDoc::GENBANKDoc()
{

}

DesignerModelComponent* GENBANKDoc::loadFromFile(QFile& file, DesignerDocComponent* docComp)
{
    if(!file.open(QFile::ReadWrite|QIODevice::Text))
        if(!file.open(QFile::ReadOnly|QIODevice::Text))
            return NULL;

    QTextStream fin(&file);
    DesignerModelComponent* newModel = DesignerModelMgr::createModel(tr("SyntheticBiologicalPartModel"), docComp);
    if(!newModel)
        return NULL;

    GENBANKDocParser parser;

    bool status = parser.parse(newModel,fin);
    file.close();
    return status ? newModel : NULL;
}

bool GENBANKDoc::saveToFile(QFile& file, DesignerModelComponent* modelComp)
{
    if(!file.open(QFile::ReadWrite))
        return false;
    QTextStream stream(&file);
    for(int i=0;i<modelComp->getModel().property("length").toInt32();i++)
    {
        QScriptValue content;
        if(modelComp->getModel().property(i).property("*partsregistry.org*").property("newcontent").property("length").toInt32()==0)
            content=modelComp->getModel().property(i).property("*partsregistry.org*").property("content");
        else
            content=modelComp->getModel().property(i).property("*partsregistry.org*").property("newcontent");
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
