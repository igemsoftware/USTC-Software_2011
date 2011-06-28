#ifndef ASSEMBLYITEMBRICK_H
#define ASSEMBLYITEMBRICK_H

#include <QGraphicsPixmapItem>
#include <QString>

#include <views/assemblyview/AssemblyLib.h>

class AssemblyItemBrick : public QGraphicsPixmapItem
{
public:
    explicit AssemblyItemBrick( QString & setName , QGraphicsItem *parent = 0 );

signals:

public slots:

private:
    QString name;
};

#endif // ASSEMBLYITEMBRICK_H
