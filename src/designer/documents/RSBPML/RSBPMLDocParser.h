#ifndef RSBPMLDOCPARSER_H
#define RSBPMLDOCPARSER_H

#include <QtXml>
#include "interfaces/DesignerModelItf.h"

class RSBPMLDocParser
{
public:
    RSBPMLDocParser();

    bool parse(DesignerModelItf& model, QDomElement& docElem);
};

#endif // RSBPMLDOCPARSER_H
