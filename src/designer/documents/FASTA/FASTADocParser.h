#ifndef FASTADOCPARSER_H
#define FASTADOCPARSER_H

#include "FASTADoc.h"
#include "models/syntheticbiologicalpartmodel/SyntheticBiologicalPart.h"

class FASTADocParser
{
public:
    FASTADocParser();
    bool parse(DesignerModelItf* model, QTextStream& fin);
    QString extract(QString &s);
    QString readWord(QString &s,int &index);
};

#endif // FASTADOCPARSER_H
