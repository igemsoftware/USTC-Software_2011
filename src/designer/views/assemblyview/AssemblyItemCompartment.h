#ifndef ASSEMBLYITEMCOMPARTMENT_H
#define ASSEMBLYITEMCOMPARTMENT_H

#include "AssemblyItemBase.h"
#include "AssemblyLib.h"
#include "AssemblyItemPlasmid.h"
#include "AssemblyItemMolecule.h"

class AssemblyItemCompartment : public AssemblyItemBase
{
public:
    static const char * MimeFormat;


    explicit AssemblyItemCompartment( QScriptValue & newScriptValue , QGraphicsItem *parent = 0 );
    virtual ~AssemblyItemCompartment();

    virtual QList<AssemblyItemBase*> getChildren();
    virtual bool addChild( QPointF pos , AssemblyItemBase * child );
    virtual void removeChild( AssemblyItemBase * child );
    virtual void refreshScriptValue();

protected:

private:
    QMap<QString,AssemblyItemBase*> childrenMap;
};


#endif // ASSEMBLYITEMCOMPARTMENT_H
