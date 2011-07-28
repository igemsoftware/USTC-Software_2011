#ifndef EMBLDOCPARSER_H
#define EMBLDOCPARSER_H

#include "EMBLDoc.h"
#include "models/syntheticbiologicalpartmodel/SyntheticBiologicalPart.h"

class EMBLDocParser
{
public:
    EMBLDocParser();
    bool parse(DesignerModelItf* model, QTextStream& fin);
    QString extract(QString &s);
    QString readWord(QString &s,int &index);
};


#endif // EMBLDOCPARSER_H
