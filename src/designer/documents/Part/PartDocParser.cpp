#include "PartDocParser.h"

PartDocParser::PartDocParser()
{
}
bool PartDocParser::parse(DesignerModelItf* model, QTextStream& fin ,QString type)
{
    //QList<Part> *parts=new QList<Part>();
    QScriptValue content=model->getEngine()->newArray();
    QScriptValue parts=model->getEngine()->newArray();   
    model->getEngine()->globalObject().setProperty("model",parts);
    int c=0,p=0;

    if(type=="fasta")
    {
        QScriptValue newpart;
        QString tsq="";


        while(!fin.atEnd())
        {
            QString line=fin.readLine();
            if(line.startsWith(">"))
            {
                if(newpart.property("acc").toString()!="")
                {
                    newpart.setProperty("sequence",this->extract(tsq));
                    newpart.setProperty("len",this->extract(tsq).length());
                    parts.setProperty(p,newpart);
                    p++;
                }
                newpart = model->getEngine()->newObject();
                tsq="";
                {
                    int t=line.indexOf("acc=",0);
                    if(t>0)
                        newpart.setProperty("acc",line.mid(t+4,line.indexOf("|",t)-t-4).trimmed());
                    t=line.indexOf("descr=",0);
                    if(t>0)
                        newpart.setProperty("descr",line.mid(t+6,line.indexOf("|",t)-t-6).trimmed());
                }
                if(line.indexOf("=")==-1)
                {
                    int t=1;
                    newpart.setProperty("acc",this->readWord(line,t));
                    newpart.setProperty("status",this->readWord(line,t));
                    newpart.setProperty("num",this->readWord(line,t));
                    newpart.setProperty("type",this->readWord(line,t));
                    t=line.indexOf('"');
                    newpart.setProperty("descr",line.mid(t+1,line.indexOf('"',t+1)-t-1).trimmed());
                }
            }
            else
                tsq+=line;
            if(fin.atEnd())
            {
                if(!newpart.isNull())
                {
                    newpart.setProperty("sequence",this->extract(tsq));
                    parts.setProperty(p,newpart);
                }
            }
            content.setProperty(c,line);
            c++;
        }
    }
//    else if(model.type=="plain")
//    {
//        Part *p=new Part();
//        QString tsq="";
//        while(!fin.atEnd())
//        {
//            QString line=fin.readLine();
//            tsq+=line;
//            model.content->append(line);
//        }
//        p->sq=this->extract(tsq);
//        p->len=QString::number(p->sq.length())+"bp";
//        model.parts->append(*p);
//    }
//    else if(model.type=="gcg")
//    {
//        Part *p=new Part();
//        QString tsq="";
//        bool issq=false;
//        while(!fin.atEnd())
//        {
//            QString line=fin.readLine();
//            if(line.startsWith("AC "))
//            {
//                QString acc=line.mid(3,line.indexOf(";",0)-3).trimmed();
//                p->acc=acc;
//            }
//            else if(line.startsWith("DE "))
//            {
//                QString desc=line.mid(3,line.indexOf(";",0)-3).trimmed();
//                p->descr=desc;
//            }
//            else if(issq&&p)
//            {
//                tsq+=line;
//            }
//            else if(line.indexOf("length:",0)!=-1)
//            {
//                issq=true;
//            }
//            model.content->append(line);
//        }
//        p->sq=this->extract(tsq);
//        p->len=QString::number(p->sq.length())+"bp";
//        model.parts->append(*p);
//    }
//    else if(model.type=="embl")
//    {
//        Part *p=NULL;
//        QString tsq="";
//        bool issq;
//        while(!fin.atEnd())
//        {
//            QString line=fin.readLine();
//            if(line.indexOf("ID ",0)==0)
//            {
//                p=new Part();
//            }
//            else if(line.startsWith("AC ")&&p)
//            {
//                QString acc=line.mid(3,line.indexOf(";",0)-3).trimmed();
//                p->acc=acc;
//            }
//            else if(line.startsWith("DE ")&&p)
//            {
//                QString desc=line.mid(3,line.indexOf(";",0)-3).trimmed();
//                p->descr=desc;
//            }
//            else if(line.startsWith("//")&&p)
//            {
//                p->sq=this->extract(tsq);
//                p->len=QString::number(p->sq.length())+"bp";
//                model.parts->append(*p);
//                p=NULL;
//                issq=false;
//                tsq="";
//            }
//            else if(issq&&p)
//            {
//                tsq+=line;
//            }
//            else if(line.startsWith("SQ ")&&p)
//            {
//                issq=true;
//            }
//            model.content->append(line);
//        }
//    }
//    else if(model.type=="genbank"||model.type==("genomatix"))
//    {
//        Part *p=NULL;
//        QString tsq="";
//        bool issq=false;
//        while(!fin.atEnd())
//        {
//            QString line=fin.readLine();
//            if(line.startsWith("LOCUS"))
//            {
//                p=new Part();
//            }
//            else if(line.startsWith("ACCESSION")&&p)
//            {
//                QString acc=line.mid(9,line.indexOf(";",0)-9).trimmed();
//                p->acc=acc;
//            }
//            else if(line.startsWith("DEFINITION")&&p)
//            {
//                QString desc=line.mid(10,line.indexOf(";",0)-10).trimmed();
//                p->descr=desc;
//            }
//            else if(line.startsWith("//")&&p)
//            {
//                p->sq=this->extract(tsq);
//                p->len=QString::number(p->sq.length())+"bp";
//                model.parts->append(*p);
//                p=NULL;
//                issq=false;
//                tsq="";
//            }
//            else if(issq&&p)
//            {
//                tsq+=line;
//            }
//            else if(line.startsWith("ORIGIN")&&p)
//            {
//                issq=true;
//            }
//            model.content->append(line);
//        }
//    }
//    else if(model.type=="ig")
//    {
//        Part *p=NULL;
//        QString tsq="";
//        QString des="";
//        bool issq=true;
//        while(!fin.atEnd())
//        {
//            QString line=fin.readLine();
//            if(line.startsWith(";"))
//            {
//                if(issq)
//                {
//                    p=new Part();
//                    issq=false;
//                }
//                des+=line.mid(1,line.length()-1).trimmed();
//            }
//            else if((line.endsWith("1")||line.endsWith("2"))&&p)
//            {
//                tsq+=line;
//                p->sq=this->extract(tsq);
//                p->descr=des;
//                p->len=QString::number(p->sq.length())+"bp";
//                model.parts->append(*p);
//                p=NULL;
//                tsq="";
//                des="";
//            }
//            else if(issq&&p)
//            {
//                tsq+=line;
//            }
//            else if(!line.startsWith(";")&& !issq &&p)
//            {
//                p->acc=line.trimmed();
//                issq=true;
//            }
//            model.content->append(line);
//        }
//    }

//    if(model.parts->count()==0)
//        return false;
//    else
        if(parts.property("length").toInt32()==0)
            return false;
        else
            return true;
}

QString PartDocParser::extract(QString &s)
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

QString PartDocParser::readWord(QString &s, int &index)
{
    QString t=s.mid(index,s.indexOf(" ",index)-index).trimmed();
    index=s.indexOf(" ",index)+1;
    return t;
}
