#ifndef RSBPMLPARSER_H
#define RSBPMLPARSER_H

#include "documents/common/designerxmldocparser/DesignerXMLDocParser.h"

class RSBPMLParser : public DesignerXMLDocParser
{
public:
    bool parse(DesignerModelComponent* model, QDomDocument& elem);

};

#endif // RSBPMLPARSER_H
