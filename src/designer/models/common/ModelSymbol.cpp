#include "ModelSymbol.h"

QScriptValue copyFromScriptValue( QScriptEngine * engine , QScriptValue source )
{
    if( !source.isObject() ) return source;
    QScriptValue copy = engine->newObject();
    QScriptValueIterator iter(source);
    while( iter.hasNext() )
    {
        iter.next();
        copy.setProperty( iter.name() , iter.value() );
    }
    return copy;
}
