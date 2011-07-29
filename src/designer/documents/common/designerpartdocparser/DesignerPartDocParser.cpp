#include "DesignerPartDocParser.h"

DesignerPartDocParser::DesignerPartDocParser()
{    
}

QString DesignerPartDocParser::generateSequence(QString &s)
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
