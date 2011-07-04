#ifndef SBMLDOCPARSER_H
#define SBMLDOCPARSER_H

#include "DesignerModelItf.h"

class SBMLDocParser
{
public:
    SBMLDocParser();

    bool parse(DesignerModelItf& model, QDomElement& docElem);
};

#endif // SBMLDOCPARSER_H
