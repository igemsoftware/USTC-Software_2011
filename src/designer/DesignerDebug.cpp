#include "DesignerDebug.h"

#ifdef DEBUG

QDebug operator<< (QDebug d, const QScriptValue & s )
{
    QList<QScriptValue> workdoneList;
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
                bool found = false;
                for(int i=0;i<workdoneList.length();i++)
                {
                    if(iter.value().strictlyEquals(workdoneList[i]))
                    {
                        found = true;
                        break;
                    }
                }
                if(!found )
                    worklist.push_back(iter.value());
                d << "\t\t\t = " << &worklist.last() <<endl;
            }
        }
        d<<"End of Debug information for this QtScript object"<<endl;
        workdoneList.push_back(worklist.first());
        worklist.pop_front();
    }
    return d;
}

#endif
