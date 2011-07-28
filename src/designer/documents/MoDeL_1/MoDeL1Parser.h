#ifndef MODEL1PARSER_H
#define MODEL1PARSER_H

#include "documents/common/designerxmldocparser/DesignerXMLDocParser.h"

class MoDeL1Parser : public DesignerXMLDocParser
{
public:
    bool parse(DesignerModelItf* model, QDomDocument& elem);

};



#endif // MODEL1PARSER_H
