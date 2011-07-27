#ifndef PART_H
#define PART_H
#include <QtCore>

class Part
{
public:
    QMap<QString,QPair<QString,QString> > properties;

public:
    Part();
};

#endif // PART_H
