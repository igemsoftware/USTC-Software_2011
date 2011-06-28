#ifndef ASSEMBLYITEMPLASMID_H
#define ASSEMBLYITEMPLASMID_H

#include <QGraphicsLineItem>
#include <QString>
#include <QList>

#include <views/assemblyview/AssemblyLib.h>
#include <views/assemblyview/AssemblyItemBrick.h>

class AssemblyItemPlasmid : public QGraphicsLineItem
{
public:
    explicit AssemblyItemPlasmid( QString & setName , QGraphicsItem *parent = 0 );
    QString name;

    static const char * MimeFormat;

private:
    QList<AssemblyItemBrick*> bricks;

};

#endif // ASSEMBLYITEMPLASMID_H
