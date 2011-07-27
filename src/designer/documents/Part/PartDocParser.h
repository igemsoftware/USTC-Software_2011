#ifndef PARTDOCPARSER_H
#define PARTDOCPARSER_H

#include "PartDoc.h"
#include "models/syntheticbiologicalpartmodel/SyntheticBiologicalPart.h"

class PartDocParser
{
public:
    PartDocParser();
    bool parse(DesignerModelItf* model, QTextStream& fin ,QString type);
    QString extract(QString &s);
    QString readWord(QString &s,int &index);
};

#endif // PARTDOCPARSER_H
