#include "DesignerDebug.h"


QDebug operator<< (QDebug d, const QScriptValue & s )
{
    QList<QScriptValue> worklist;
    worklist.push_back(s);
    while(!worklist.isEmpty())
    {
        d<<endl<<"Debug information for QtScript object ("<<&s<<")"<<endl;
        QScriptValueIterator iter(worklist.first());
        while( iter.hasNext() )
        {
            iter.next();
            d << iter.name() << ": "<< iter.value().toString()<<endl;
            if(iter.value().isObject())
            {
                worklist.push_back(iter.value());
                d << "\t\t\t = " << &worklist.last() <<endl;
            }
        }
        d<<"End of Debug information for this QtScript object"<<endl;
        worklist.pop_front();
    }
    return d;
}
