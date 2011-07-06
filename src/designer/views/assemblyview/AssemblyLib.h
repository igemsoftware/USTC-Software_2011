#ifndef ASSEMBLYLIB_H
#define ASSEMBLYLIB_H

#include <QObject>
#include <QMessageBox>

#include <QGraphicsSceneMouseEvent>
#include <QMimeData>
#include <QMap>
#include <QList>
#include <QGraphicsScene>
#include <QScriptEngine>
#include <QScriptValue>
#include "models/common/ModelSymbol.h"
#include "models/reactionnetworkmodel/ReactionNetworkDataTypes.h"

namespace AssemblyViewNameSpace
{
    extern QScriptEngine * engine;
    extern QList<QString> partTypes;
}

#include <views/assemblyview/AssemblyCreateAndDrag.h>

#define ASSEMBLY_ITEM_BRICK_HEIGHT 40
#define ASSEMBLY_ITEM_BRICK_WIDTH 40

#endif // ASSEMBLYLIB_H
