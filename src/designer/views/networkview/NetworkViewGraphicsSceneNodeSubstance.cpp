#include "NetworkViewGraphicsSceneNodeSubstance.h"
#include "NetworkViewSubstanceEditor.h"

NetworkViewGraphicsSceneNodeSubstance::NetworkViewGraphicsSceneNodeSubstance(QScriptValue value, QGraphicsItem *parent, bool isParentContainer)
    :NetworkViewGraphicsSceneNode( parent,value, QObject::tr(":/designer/assemblyview/icon_protein.png") , QObject::tr(":/designer/assemblyview/icon_protein.png") ,isParentContainer )
{
    Type="substance";
}

void NetworkViewGraphicsSceneNodeSubstance::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    NetworkViewSubstanceEditor dialog(itemObject,dynamic_cast<NetworkViewGraphicsScene *>(scene())->idSpace);
    dialog.exec();
    this->displayName->setPlainText(this->itemObject.property("name").toString());
    this->displayName->adjustSize();
    NetworkViewGraphicsItem::mouseDoubleClickEvent(event);
}
