#ifndef PARTDOCPARSER_H
#define PARTDOCPARSER_H

#include "PartDoc.h"

class PartDocParser
{
public:
    PartDocParser();
    bool parse(PartDoc& model, QTextStream& fin);    
    QString extract(QString &s);
};

#endif // PARTDOCPARSER_H
