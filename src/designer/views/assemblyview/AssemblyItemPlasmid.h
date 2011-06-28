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

signals:

public slots:

private:
    QList<AssemblyItemBrick*> bricks;
    QString name;
};

#endif // ASSEMBLYITEMPLASMID_H
