#include "PartDocParser.h"

PartDocParser::PartDocParser()
{
}
bool PartDocParser::parse(PartDoc& model, QTextStream& fin)
{
    model.parts=new QList<Part>();
    model.content=new QList<QString>();
    if(model.type=="fasta")
    {
        Part *p=NULL;
        QString tsq="";
        while(!fin.atEnd())
        {
            QString line=fin.readLine();
            if(line.startsWith(">"))
            {
                if(p)
                {
                   p->sq=tsq;
                   p->len=QString::number(p->sq.length())+"bp";
                   model.parts->append(*p);
                }
                p=new Part();
                int t=line.indexOf("acc=",0);
                if(t>0)p->acc=line.mid(t+4,line.indexOf("|",t)-t-4).trimmed();
                t=line.indexOf("descr=",0);
                if(t>0)p->descr=line.mid(t+6,line.indexOf("|",t)-t-6).trimmed();
                tsq="";
            }
            else
            {
                tsq+=line;
            }
            if(fin.atEnd())
            {
                if(p)
                {
                   p->sq=this->extract(tsq);
                   p->len=QString::number(p->sq.length())+"bp";
                   model.parts->append(*p);
                }
            }
            model.content->append(line);
        }
    }
    else if(model.type=="plain")
    {
        Part *p=new Part();
        QString tsq="";
        while(!fin.atEnd())
        {
            QString line=fin.readLine();
            tsq+=line;
            model.content->append(line);
        }
        p->sq=this->extract(tsq);
        p->len=QString::number(p->sq.length())+"bp";
        model.parts->append(*p);
    }
    else if(model.type=="gcg")
    {
        Part *p=new Part();
        QString tsq="";
        bool issq=false;
        while(!fin.atEnd())
        {
            QString line=fin.readLine();
            if(line.startsWith("AC "))
            {
                QString acc=line.mid(3,line.indexOf(";",0)-3).trimmed();
                p->acc=acc;
            }
            else if(line.startsWith("DE "))
            {
                QString desc=line.mid(3,line.indexOf(";",0)-3).trimmed();
                p->descr=desc;
            }
            else if(issq&&p)
            {
                tsq+=line;
            }
            else if(line.indexOf("length:",0)!=-1)
            {
                issq=true;
            }
            model.content->append(line);
        }
        p->sq=this->extract(tsq);
        p->len=QString::number(p->sq.length())+"bp";
        model.parts->append(*p);
    }
    else if(model.type=="embl")
    {
        Part *p=NULL;
        QString tsq="";
        bool issq;
        while(!fin.atEnd())
        {
            QString line=fin.readLine();
            if(line.indexOf("ID ",0)==0)
            {
                p=new Part();
            }
            else if(line.startsWith("AC ")&&p)
            {
                QString acc=line.mid(3,line.indexOf(";",0)-3).trimmed();
                p->acc=acc;
            }
            else if(line.startsWith("DE ")&&p)
            {
                QString desc=line.mid(3,line.indexOf(";",0)-3).trimmed();
                p->descr=desc;
            }
            else if(line.startsWith("//")&&p)
            {
                p->sq=this->extract(tsq);
                p->len=QString::number(p->sq.length())+"bp";
                model.parts->append(*p);
                p=NULL;
                issq=false;
                tsq="";
            }
            else if(issq&&p)
            {
                tsq+=line;
            }
            else if(line.startsWith("SQ ")&&p)
            {
                issq=true;
            }
            model.content->append(line);
        }
    }
    else if(model.type=="genbank"||model.type==("genomatix"))
    {
        Part *p=NULL;
        QString tsq="";
        bool issq=false;
        while(!fin.atEnd())
        {
            QString line=fin.readLine();
            if(line.startsWith("LOCUS"))
            {
                p=new Part();
            }
            else if(line.startsWith("ACCESSION")&&p)
            {
                QString acc=line.mid(9,line.indexOf(";",0)-9).trimmed();
                p->acc=acc;
            }
            else if(line.startsWith("DEFINITION")&&p)
            {
                QString desc=line.mid(10,line.indexOf(";",0)-10).trimmed();
                p->descr=desc;
            }
            else if(line.startsWith("//")&&p)
            {
                p->sq=this->extract(tsq);
                p->len=QString::number(p->sq.length())+"bp";
                model.parts->append(*p);
                p=NULL;
                issq=false;
                tsq="";
            }
            else if(issq&&p)
            {
                tsq+=line;
            }
            else if(line.startsWith("ORIGIN")&&p)
            {
                issq=true;
            }
            model.content->append(line);
        }
    }
    else if(model.type=="ig")
    {
        Part *p=NULL;
        QString tsq="";
        QString des="";
        bool issq=true;
        while(!fin.atEnd())
        {
            QString line=fin.readLine();
            if(line.startsWith(";"))
            {
                if(issq)
                {
                    p=new Part();
                    issq=false;
                }
                des+=line.mid(1,line.length()-1).trimmed();
            }
            else if((line.endsWith("1")||line.endsWith("2"))&&p)
            {
                tsq+=line;
                p->sq=this->extract(tsq);
                p->descr=des;
                p->len=QString::number(p->sq.length())+"bp";
                model.parts->append(*p);
                p=NULL;
                tsq="";
                des="";
            }
            else if(issq&&p)
            {
                tsq+=line;
            }
            else if(!line.startsWith(";")&& !issq &&p)
            {
                p->acc=line.trimmed();
                issq=true;
            }
            model.content->append(line);
        }
    }

    if(model.parts->count()==0)
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
