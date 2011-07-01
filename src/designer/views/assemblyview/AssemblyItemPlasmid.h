#ifndef ASSEMBLYITEMPLASMID_H
#define ASSEMBLYITEMPLASMID_H

#include <QGraphicsRectItem>
#include <QString>
#include <QList>

#include "AssemblyItemBase.h"
#include "AssemblyLib.h"
#include "AssemblyItemPart.h"

class AssemblyItemPlasmid : public AssemblyItemBase
{
public:
    static const char * MimeFormat;


    explicit AssemblyItemPlasmid( QString newName , QGraphicsItem *parent = 0 );
    virtual ~AssemblyItemPlasmid();

    virtual QList<AssemblyItemBase*> getChildren();
    virtual bool addChild( QPointF scenePos , AssemblyItemBase * child );
    virtual void removeChild( AssemblyItemBase * child );

    void arrangeChild();

protected:

private:
    QList<AssemblyItemBase*> childrenList;
};

#endif // ASSEMBLYITEMPLASMID_H
