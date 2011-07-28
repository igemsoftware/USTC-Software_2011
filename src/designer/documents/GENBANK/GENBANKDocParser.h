#ifndef GENBANKDOCPARSER_H
#define GENBANKDOCPARSER_H

#include "GENBANKDoc.h"
#include "models/syntheticbiologicalpartmodel/SyntheticBiologicalPart.h"

class GENBANKDocParser
{
public:
    GENBANKDocParser();
    bool parse(DesignerModelItf* model, QTextStream& fin);
    QString extract(QString &s);
    QString readWord(QString &s,int &index);
};

#endif // GENBANKDOCPARSER_H
