#ifndef SBMLPARSER_H
#define SBMLPARSER_H

#include "documents/common/designerxmldocparser/DesignerXMLDocParser.h"

class SBMLParser : public DesignerXMLDocParser
{
public:
    QDomDocument* parse(DesignerModelItf* model);

};



#endif // SBMLPARSER_H
