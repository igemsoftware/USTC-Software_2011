#ifndef FASTADOCPARSER_H
#define FASTADOCPARSER_H

#include "FASTADoc.h"
#include "models/syntheticbiologicalpartmodel/SyntheticBiologicalPart.h"
#include "documents/common/designerpartdocparser/DesignerPartDocParser.h"

class FASTADocParser
{
public:
    FASTADocParser();
    bool parse(DesignerModelComponent* model, QTextStream& fin);    
    QString readWord(QString &s,int &index);
};

#endif // FASTADOCPARSER_H
