#ifndef SBMLPARSER_H
#define SBMLPARSER_H

#include "documents/common/designerxmldocparser/DesignerXMLDocParser.h"

class SBMLParser : public DesignerXMLDocParser
{
public:
    bool parse(DesignerModelItf* model, QDomDocument& elem);

};



#endif // SBMLPARSER_H
