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
        if(!line.isEmpty())
        {
            content.setProperty(c,line);
            c++;
        }
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
            partregisty.setProperty("partsequence",DesignerPartDocParser::generateSequence(tsq));
            partregisty.setProperty("*partsregistry.org*",newEMBL);
            newEMBL.setProperty("content",content);
            EMBLs.setProperty(p,partregisty);


            newEMBL=model->getEngine()->newObject();
            partregisty=model->getEngine()->newObject();
            content=model->getEngine()->newArray();

            p++;c=0;tsq="";issq=false;
        }
        else if(line.startsWith("SQ"))
            issq=true;        
    }
    if(EMBLs.property("length").toInt32()==0)
        return false;
    else
        return true;
}

QString EMBLDocParser::readWord(QString &s, int &index)
{
    while(s.mid(index,1)==" "||s.mid(index,1)==";")
        index++;
    QString  t;
    if(s.indexOf(";")!=-1&&s.indexOf(" ")!=-1)
        t=s.mid(index,qMin(s.indexOf(" ",index),s.indexOf(";",index))-index).trimmed();
    else if(s.indexOf(";")==-1)
        t=s.mid(index,s.indexOf(" ",index)-index).trimmed();
    else if(s.indexOf(" ")==-1)
        t=s.mid(index,s.indexOf(";",index)-index).trimmed();
    else
        t=s.mid(index,s.length()-index);
    index=s.indexOf(" ",index)+1;
    return t;
}
