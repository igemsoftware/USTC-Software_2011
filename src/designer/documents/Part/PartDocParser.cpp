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
        Part *p;
        QString tsq="";
        while(!fin.atEnd())
        {
            QString tmp=fin.readLine();
            if(tmp.at(0)=='>')
            {
                if(p)
                {
                   p->sq=tsq;
                   model.parts->append(*p);
                }
                p=new Part();
                int t=tmp.indexOf("acc=",0);
                if(t>0)p->ass=tmp.mid(t+4,tmp.indexOf("|",t)-t-4);
                t=tmp.indexOf("descr=",0);
                if(t>0)p->descr=tmp.mid(t+6,tmp.indexOf("|",t)-t-6);
                t=tmp.indexOf("len=",0);
                if(t>0)p->len=tmp.mid(t+4,tmp.indexOf("|",t)-t-4);
                tsq="";
            }
            else
            {
                tsq+=tmp;
            }
            if(fin.atEnd())
            {
                if(p)
                {
                   p->sq=tsq;
                   model.parts->append(*p);
                }
            }
            model.content->append(tmp);
        }
    }
}
