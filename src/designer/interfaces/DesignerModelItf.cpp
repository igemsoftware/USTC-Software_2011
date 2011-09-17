#include <QtDebug>
#include <QScriptValueIterator>

#include "DesignerModelItf.h"

DesignerModelComponent::DesignerModelComponent(DesignerDocComponent *newDoc) :
    currentDoc(newDoc),
    modified(false)
{
}


