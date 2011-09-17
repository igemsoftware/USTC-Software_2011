#include "GENBANKDocParser.h"

GENBANKDocParser::GENBANKDocParser()
{
}
bool GENBANKDocParser::parse(DesignerModelComponent* model, QTextStream& fin)
{
    QScriptValue GENBANKs=model->getEngine()->newArray();
    model->getEngine()->globalObject().setProperty("model",GENBANKs);
    int c=0,p=0;


        QScriptValue content=model->getEngine()->newArray();
        QScriptValue newGENBANK=model->getEngine()->newObject();
        QScriptValue partregisty=model->getEngine()->newObject();
        QString tsq="";
        bool issq=false;

    while(!fin.atEnd())
    {
        QString line=fin.readLine();
        if(!line.isEmpty())
        {
            content.setProperty(c,line);
            c++;
        }
        if(line.startsWith("LOCUS"))
        {
            int t=5;
            newGENBANK.setProperty("part_name",this->readWord(line,t));
            newGENBANK.setProperty("part_length",this->readWord(line,t));
            newGENBANK.setProperty("part_type",this->readWord(line,t));
            newGENBANK.setProperty("part_form",this->readWord(line,t));
        }
        else if(line.startsWith("DEFINITION"))
            newGENBANK.setProperty("part_descr",line.mid(10,line.length()-10).trimmed());
        else if(!line.startsWith("//")&&issq)
            tsq+=line;
        else if(line.startsWith("//"))
        {
            partregisty.setProperty("partsequence",DesignerPartDocParser::generateSequence(tsq));
            partregisty.setProperty("*partsregistry.org*",newGENBANK);
            newGENBANK.setProperty("part_length",DesignerPartDocParser::generateSequence(tsq).length());
            newGENBANK.setProperty("content",content);
            GENBANKs.setProperty(p,partregisty);

            newGENBANK=model->getEngine()->newObject();
            partregisty=model->getEngine()->newObject();
            content=model->getEngine()->newArray();

            p++;c=0;tsq="";issq=false;
        }
        else if(line.startsWith("ORIGIN"))
            issq=true;        
    }
    if(GENBANKs.property("length").toInt32()==0)
        return false;
    else
        return true;
}

QString GENBANKDocParser::readWord(QString &s, int &index)
{
    while(s.mid(index,1)==" ")
        index++;
    QString t=s.mid(index,s.indexOf("  ",index)-index).trimmed();
    index=s.indexOf("  ",index)+1;
    return t;
}
