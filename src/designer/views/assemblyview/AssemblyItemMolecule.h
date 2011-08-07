#ifndef ASSEMBLYITEMMOLECULE_H
#define ASSEMBLYITEMMOLECULE_H

#include <QString>
#include "AssemblyLib.h"
#include "AssemblyItemBase.h"

class AssemblyItemMolecule : public AssemblyItemBase
{
public:
    static const char * MimeFormat;


    explicit AssemblyItemMolecule( QScriptValue & newScriptValue , QGraphicsItem *parent = 0 );
    virtual ~AssemblyItemMolecule();

    virtual bool addChild(QPointF scenePos, AssemblyItemBase *child);
};

#endif // ASSEMBLYITEMMOLECULE_H
