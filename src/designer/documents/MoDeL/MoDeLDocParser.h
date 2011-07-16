#ifndef MODELDOCPARSER_H
#define MODELDOCPARSER_H

#include <QTextStream>
#include "interfaces/DesignerModelItf.h"

class MoDeLDocParser
{
public:
    MoDeLDocParser();

    bool parse( DesignerModelItf& model, QTextStream& fin );
};

#endif // MODELDOCPARSER_H
