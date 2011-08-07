#ifndef MODELDOCPARSER_H
#define MODELDOCPARSER_H

#include <QTextStream>
#include "interfaces/DesignerModelItf.h"

class MoDeLDocParser
{
public:
    MoDeLDocParser();

    bool parse( DesignerModelItf& model, QTextStream& fin );
    bool readCompartment( QScriptEngine * engine , QSet<QString> & parameterSet , QScriptValue & compartment , QString & strCompartment, QString tag );

};

#endif // MODELDOCPARSER_H
