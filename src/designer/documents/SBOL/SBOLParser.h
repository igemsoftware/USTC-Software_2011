#ifndef SBOLPARSER_H
#define SBOLPARSER_H

#include "documents/common/designerxmldocparser/DesignerXMLDocParser.h"

class SBOLParser : public DesignerXMLDocParser
{
public:
    bool parse(DesignerModelItf* model, QDomDocument& elem);

};


#endif // SBOLPARSER_H
