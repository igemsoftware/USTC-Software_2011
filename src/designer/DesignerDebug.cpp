#include "DesignerDebug.h"


QDebug operator<< (QDebug d, const QScriptValue & s )
{
    d<<endl<<"Debug information for QtScript object ("<<&s<<")"<<endl;
    QScriptValueIterator iter(s);
    while( iter.hasNext() )
    {
        iter.next();
        d.space() << iter.name() << ": "<< iter.value().toString()<<endl;
    }
    d<<"End of Debug information for this QtScript object"<<endl;

    return d;
}
