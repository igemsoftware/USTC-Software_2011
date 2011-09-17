#ifndef ASSEMBLYITEMPART_H
#define ASSEMBLYITEMPART_H

#include <QString>
#include "AssemblyLib.h"
#include "AssemblyItemBase.h"

class AssemblyItemPart : public AssemblyItemBase
{
public:
    static const char * MimeFormat;


    explicit AssemblyItemPart( QScriptValue & newScriptValue , QGraphicsItem *parent = 0 );
    virtual ~AssemblyItemPart();

    virtual bool addChild(QPointF scenePos, AssemblyItemBase *child);

    virtual void setScriptValue(QScriptValue &newScriptValue);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
private:
};

#endif // ASSEMBLYITEMPART_H
