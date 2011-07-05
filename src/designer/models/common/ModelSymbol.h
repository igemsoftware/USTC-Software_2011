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
    typedef QScriptValueList mathsegexpr_t;  // [ [expr, start1, end1], event, [expr2, start2, end2], event, ... [expr-n, start-n, +inf]]	
    typedef qreal precisevalue_t;
    typedef bool predicate_t;
}

Q_DECLARE_METATYPE(QScriptString);
Q_DECLARE_METATYPE(QList<QScriptString>);
Q_DECLARE_METATYPE(QScriptValueList);

template<class T>
QScriptValue convertModelTypeToScriptValue(QScriptEngine* engine, T value)
{
    return qScriptValueFromValue(engine, value);
}

template<class R>
QScriptValue convertModelTypeToScriptValue(QScriptEngine* engine, QList<R>& value)
{
    return qScriptValueFromSequence(engine, value);
}

struct PropertyDescriptor
{
        PropertyDescriptor( QString newProperty , QVariant::Type newType )
            : property(newProperty) , type(newType) {}
        QString property;
        QVariant::Type type;
};


#endif // MODELSYMBOL_H
