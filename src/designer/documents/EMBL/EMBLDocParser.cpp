#include "EMBLDocParser.h"

EMBLDocParser::EMBLDocParser()
{    
}
bool EMBLDocParser::parse(DesignerModelItf* model, QTextStream& fin)
{
    QScriptValue EMBLs=model->getEngine()->newArray();
    model->getEngine()->globalObject().setProperty("model",EMBLs);
    int c=0,p=0;


        QScriptValue content=model->getEngine()->newArray();
        QScriptValue newEMBL=model->getEngine()->newObject();
        QScriptValue partregisty=model->getEngine()->newObject();
        QString tsq="";
        bool issq=false;

    while(!fin.atEnd())
    {
        QString line=fin.readLine();
        if(line.startsWith("ID"))
        {
            int t=2;
            newEMBL.setProperty("part_name",this->readWord(line,t));
            newEMBL.setProperty("part_status",this->readWord(line,t));
            newEMBL.setProperty("part_type",this->readWord(line,t));
        }
        else if(line.startsWith("DE"))
            newEMBL.setProperty("part_descr",line.mid(2,line.length()-2).trimmed());
        else if(!line.startsWith("//")&&issq)
            tsq+=line;
        else if(line.startsWith("//"))
        {
            partregisty.setProperty("partsequence",this->extract(tsq));
            partregisty.setProperty("*partsregistry.org*",newEMBL);
            newEMBL.setProperty("content",content);
            EMBLs.setProperty(p,partregisty);
            p++;c=0;tsq="";issq=false;

            newEMBL=model->getEngine()->newObject();
            partregisty=model->getEngine()->newObject();
        }
        else if(line.startsWith("SQ"))
            issq=true;
        content.setProperty(c,line);
        c++;
    }
    if(EMBLs.property("length").toInt32()==0)
        return false;
    else
        return true;
}

QString EMBLDocParser::extract(QString &s)
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

QString EMBLDocParser::readWord(QString &s, int &index)
{
    while(s.mid(index,1)==" "||s.mid(index,1)==";")
        index++;
    QString t=s.mid(index,qMin(s.indexOf(" ",index),s.indexOf(";",index))-index).trimmed();
    index=s.indexOf(" ",index)+1;
    return t;
}
