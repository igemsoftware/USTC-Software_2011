#include "GENBANKDocParser.h"

GENBANKDocParser::GENBANKDocParser()
{
}
bool GENBANKDocParser::parse(DesignerModelItf* model, QTextStream& fin)
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
        if(line.startsWith("LOCUS"))
        {
            int t=5;
            newGENBANK.setProperty("part_name",this->readWord(line,t));
            newGENBANK.setProperty("part_length",this->readWord(line,t));
            newGENBANK.setProperty("part_type",this->readWord(line,t));
            newGENBANK.setProperty("part_form",this->readWord(line,t));
        }
        else if(line.startsWith("DEFINITION"))
            newGENBANK.setProperty("part_descr",line.mid(2,line.length()-2).trimmed());
        else if(!line.startsWith("//")&&issq)
            tsq+=line;
        else if(line.startsWith("//"))
        {
            partregisty.setProperty("partsequence",this->extract(tsq));
            partregisty.setProperty("*partsregistry.org*",newGENBANK);
            newGENBANK.setProperty("content",content);
            GENBANKs.setProperty(p,partregisty);

            newGENBANK=model->getEngine()->newObject();
            partregisty=model->getEngine()->newObject();
            content=model->getEngine()->newArray();

            p++;c=0;tsq="";issq=false;
        }
        else if(line.startsWith("ORIGIN"))
            issq=true;
        content.setProperty(c,line);
        c++;
    }
    if(GENBANKs.property("length").toInt32()==0)
        return false;
    else
        return true;
}

QString GENBANKDocParser::extract(QString &s)
{
    s=s.toLower();
    QString t="";
    int l=s.length();
    for(int i=0;i<l;i++)
    {
        QChar c=s.at(i);
        if(c=='a'||c=='t'||c=='c'||c=='g'||c=='u')
            t+=QString(c);
    }
    return t;
}

QString GENBANKDocParser::readWord(QString &s, int &index)
{
    while(s.mid(index,1)==" ")
        index++;
    QString t=s.mid(index,s.indexOf("  ",index)-index).trimmed();
    index=s.indexOf("  ",index)+1;
    return t;
}
