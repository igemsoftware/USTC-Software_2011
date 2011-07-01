#ifndef ASSEMBLYITEMCOMPARTMENT_H
#define ASSEMBLYITEMCOMPARTMENT_H

#include "AssemblyItemBase.h"
#include "AssemblyLib.h"
#include "AssemblyItemPlasmid.h"

class AssemblyItemCompartment : public AssemblyItemBase
{
public:
    static const char * MimeFormat;


    explicit AssemblyItemCompartment( QString newName , QGraphicsItem *parent = 0 );
    virtual ~AssemblyItemCompartment();

    virtual QList<AssemblyItemBase*> getChildren();
    virtual bool addChild( QPointF scenePos , AssemblyItemBase * child );
    virtual void removeChild( AssemblyItemBase * child );


protected:

private:
    QMap<QString,AssemblyItemBase*> childrenMap;
};


#endif // ASSEMBLYITEMCOMPARTMENT_H
