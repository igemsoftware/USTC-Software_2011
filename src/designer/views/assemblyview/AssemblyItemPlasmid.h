#ifndef ASSEMBLYITEMPLASMID_H
#define ASSEMBLYITEMPLASMID_H

#include <QGraphicsRectItem>
#include <QString>
#include <QList>

#include <views/assemblyview/AssemblyLib.h>
#include <views/assemblyview/AssemblyItemBrick.h>

class AssemblyItemPlasmid : public QGraphicsRectItem
{
public:
    explicit AssemblyItemPlasmid( QString & setName , QGraphicsItem *parent = 0 );
    QString name;

    enum{
        DefaultHeight = ASSEMBLY_ITEM_BRICK_HEIGHT ,
        DefaultWeight = ASSEMBLY_ITEM_BRICK_WIDTH
    };

    static const char * MimeFormat;

private:
    QList<AssemblyItemBrick*> bricks;

};

#endif // ASSEMBLYITEMPLASMID_H
