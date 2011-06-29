#ifndef ASSEMBLYITEMBRICK_H
#define ASSEMBLYITEMBRICK_H

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QString>

#include <views/assemblyview/AssemblyLib.h>

class AssemblyItemBrick : public QGraphicsPixmapItem
{
public:
    explicit AssemblyItemBrick( QString & setName , QGraphicsItem *parent = 0 );
    virtual ~AssemblyItemBrick();

    QString name;

    static const char * MimeFormat;

private:
    QGraphicsTextItem * displayName;
};

#endif // ASSEMBLYITEMBRICK_H
