#ifndef RSBPMLPARSER_H
#define RSBPMLPARSER_H

#include "documents/common/designerxmldocparser/DesignerXMLDocParser.h"

class RSBPMLParser : public DesignerXMLDocParser
{
public:
    void parse(DesignerModelItf* model, QDomElement elem, QScriptValue parent);

};

#endif // RSBPMLPARSER_H
