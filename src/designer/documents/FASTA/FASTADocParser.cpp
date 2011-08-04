#include "FASTADocParser.h"

FASTADocParser::FASTADocParser()
{
}
bool FASTADocParser::parse(DesignerModelItf* model, QTextStream& fin)
{
    QScriptValue FASTAs=model->getEngine()->newArray();
    model->getEngine()->globalObject().setProperty("model",FASTAs);
    int c=0,p=0;


        QScriptValue content;
        QScriptValue newFASTA;
        QScriptValue partregisty;
        QString tsq="";


        while(!fin.atEnd())
        {
            QString line=fin.readLine();
            if(line.startsWith(">"))
            {
                if(newFASTA.property("part_name").toString()!="")
                {
                    partregisty.setProperty("partsequence",DesignerPartDocParser::generateSequence(tsq));
                    newFASTA.setProperty("content",content);
                    FASTAs.setProperty(p,partregisty);
                    partregisty.setProperty("*partsregistry.org*",newFASTA);
                    p++;
                }
                newFASTA = model->getEngine()->newObject();
                partregisty=model->getEngine()->newObject();
                content=model->getEngine()->newArray();
                tsq="";c=0;

                {
                    int t=line.indexOf("acc=",0);
                    if(t>0)
                        newFASTA.setProperty("part_name",line.mid(t+4,line.indexOf("|",t)-t-4).trimmed());
                    t=line.indexOf("descr=",0);
                    if(t>0)
                        newFASTA.setProperty("part_descr",line.mid(t+6,line.indexOf("|",t)-t-6).trimmed());
                    t=line.indexOf("type=",0);
                    if(t>0)
                        newFASTA.setProperty("part_type",line.mid(t+5,line.indexOf("|",t)-t-5).trimmed());
                    else if(t==-1)
                        newFASTA.setProperty("part_type","other");
                }
                if(line.indexOf("=")==-1)
                {
                    int t=1;
                    newFASTA.setProperty("part_name",this->readWord(line,t));
                    newFASTA.setProperty("part_status",this->readWord(line,t));
                    newFASTA.setProperty("part_id",this->readWord(line,t));
                    newFASTA.setProperty("part_type",this->readWord(line,t));
                    t=line.indexOf('"');
                    newFASTA.setProperty("part_descr",line.mid(t+1,line.indexOf('"',t+1)-t-1).trimmed());
                }
            }
            else
                tsq+=line;
            if(fin.atEnd())
            {
                if(!newFASTA.isNull())
                {                    
                    partregisty.setProperty("partsequence",DesignerPartDocParser::generateSequence(tsq));
                    newFASTA.setProperty("content",content);
                    FASTAs.setProperty(p,partregisty);
                    partregisty.setProperty("*partsregistry.org*",newFASTA);
                }
            }
            if(!line.isEmpty())
            {
                content.setProperty(c,line);
                c++;
            }
        }


        if(FASTAs.property("length").toInteger()==0)
            return false;
        else
            return true;
}

QString FASTADocParser::readWord(QString &s, int &index)
{
    while(s.mid(index,1)==" ")
        index++;
    QString t=s.mid(index,s.indexOf(" ",index)-index).trimmed();
    index=s.indexOf(" ",index)+1;
    return t;
}
