#ifndef MODELSYMBOL_H
#define MODELSYMBOL_H

#include <QList>
#include <QScriptString>
#include <QScriptValueList>

namespace lachesis
{
    typedef QScriptString symbol_t;
    typedef QList<QScriptString> symbollist_t;
    typedef QScriptValueList valuelist_t;

    typedef QScriptValueList mathexpr_t;
    typedef QScriptValueList mathexpr_segbytime_t;  // [ [expr, start1, end1], event, [expr2, start2, end2], event, ... [expr-n, start-n, +inf]]

    typedef double precisevalue_t;

}

#endif // MODELSYMBOL_H
