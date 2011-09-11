#ifndef GENBANKDOCPARSER_H
#define GENBANKDOCPARSER_H

#include "GENBANKDoc.h"
#include "models/syntheticbiologicalpartmodel/SyntheticBiologicalPart.h"
#include "documents/common/designerpartdocparser/DesignerPartDocParser.h"

class GENBANKDocParser
{
public:
    GENBANKDocParser();
    bool parse(DesignerModelComponent* model, QTextStream& fin);    
    QString readWord(QString &s,int &index);
};

#endif // GENBANKDOCPARSER_H
