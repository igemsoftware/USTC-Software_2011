#ifndef USMLPARSER_H
#define USMLPARSER_H

#include "documents/common/designerxmldocparser/DesignerXMLDocParser.h"

class USMLParser : public DesignerXMLDocParser
{
public:
    bool parse(DesignerModelItf* model, QDomDocument& elem);

};



#endif // USMLPARSER_H
