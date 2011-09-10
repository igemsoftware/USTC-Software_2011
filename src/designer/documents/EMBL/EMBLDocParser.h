#ifndef EMBLDOCPARSER_H
#define EMBLDOCPARSER_H

#include "EMBLDoc.h"
#include "models/syntheticbiologicalpartmodel/SyntheticBiologicalPart.h"
#include "documents/common/designerpartdocparser/DesignerPartDocParser.h"

class EMBLDocParser
{
public:
    EMBLDocParser();
    bool parse(DesignerModelComponent* model, QTextStream& fin);    
    QString readWord(QString &s,int &index);
};


#endif // EMBLDOCPARSER_H
