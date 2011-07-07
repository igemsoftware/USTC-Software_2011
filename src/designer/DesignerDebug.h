#ifndef DESIGNERDEBUG_H
#define DESIGNERDEBUG_H

#include <QtDebug>
#include <QtScript>

QDebug operator<< (QDebug d, const QScriptValue & s );

#endif // DESIGNERDEBUG_H
