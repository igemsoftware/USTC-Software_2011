#ifndef ASSEMBLYITEMBRICK_H
#define ASSEMBLYITEMBRICK_H

#include <QGraphicsPixmapItem>
#include <QString>

#include <views/assemblyview/AssemblyLib.h>

class AssemblyItemBrick : public QGraphicsPixmapItem
{
public:
    explicit AssemblyItemBrick( QString & setName , QGraphicsItem *parent = 0 );
    QString name;

    static const char * MimeFormat;

private:
};

#endif // ASSEMBLYITEMBRICK_H
