#ifndef NETWORKVIEWGRAPHICSITEM_H
#define NETWORKVIEWGRAPHICSITEM_H

#include <QtScript>

class NetworkViewGraphicsItem
{
public:
    NetworkViewGraphicsItem(const QScriptValue& value);

public:
    QScriptValue itemObject;


};

#endif // NETWORKVIEWGRAPHICSITEM_H
