#ifndef DESIGNERDEBUG_H
#define DESIGNERDEBUG_H

#ifdef DEBUG
#include <QtDebug>
#include <QtScript>

QDebug operator<< (QDebug d, const QScriptValue & s );

#endif

#endif // DESIGNERDEBUG_H
