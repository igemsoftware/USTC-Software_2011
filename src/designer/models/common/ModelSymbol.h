#ifndef MODELSYMBOL_H
#define MODELSYMBOL_H

#include <QList>
#include <QScriptString>
#include <QScriptValueList>

namespace lachesis
{
    typedef QScriptString symbol_t;
	Q_DECLARE_METATYPE(symbol_t);
	
    typedef QList<QScriptString> symbollist_t;
	Q_DECLARE_METATYPE(symbollist_t);
	
    typedef QScriptValueList valuelist_t;
	Q_DECLARE_METATYPE(valuelist_t);
	
    typedef QScriptValueList mathexpr_t;
	Q_DECLARE_METATYPE(mathexpr_t);
	
    typedef QScriptValueList mathsegexpr_t;  // [ [expr, start1, end1], event, [expr2, start2, end2], event, ... [expr-n, start-n, +inf]]
	Q_DECLARE_METATYPE(mathsegexpr_t);
	
    typedef double precisevalue_t;
	Q_DECLARE_METATYPE(precisevalue_t);
	
	
	struct PropertyDescriptor
	{
		PropertyDescriptor( QString newProperty , QVariant::Type newType ) : property(newProperty) , type(newType) {}
		QString property;
		QVariant::Type type;
	};

}


#endif // MODELSYMBOL_H
