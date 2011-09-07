#include "NetworkViewGraphicsSceneNodeReaction.h"
#include "models/common/ModelSymbol.h"
#include "NetworkViewReactionEditor.h"

NetworkViewGraphicsSceneNodeReaction::NetworkViewGraphicsSceneNodeReaction(QScriptValue value, QGraphicsItem *parent, bool isParentContainer)
    :NetworkViewGraphicsSceneNode( parent,value, QObject::tr(":/designer/assemblyview/icon_mol.png") , QObject::tr(":/designer/assemblyview/icon_mol.png") ,isParentContainer )
{
    Type="reaction";
}

void NetworkViewGraphicsSceneNodeReaction::refreshScriptValue()
{
    QScriptValueList reactants;
    QScriptEngine *engine;
    QScriptValueList products;
    QScriptValue newvalue;

    engine=dynamic_cast<NetworkViewGraphicsScene *>(scene())->model->getEngine();
    foreach(NetworkViewGraphicsSceneEdge *edge,edgeList)
    {
        newvalue=engine->newObject();
        newvalue.setProperty("*tag*","speciesReference");
        if(edge->edgeNode1==this)
        {
            newvalue.setProperty("species",edge->edgeNode2->itemObject.property("id"));
            products.push_back(newvalue);
        }
        else if(edge->edgeNode2==this)
        {
            newvalue.setProperty("species",edge->edgeNode1->itemObject.property("id"));
            reactants.push_back(newvalue);
        }
    }
    this->itemObject.setProperty( "reactants" , convertModelTypeToScriptValue(engine,reactants));
    this->itemObject.setProperty( "products" , convertModelTypeToScriptValue(engine,products));
}

void NetworkViewGraphicsSceneNodeReaction::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    NetworkViewReactionEditor dialog(itemObject,dynamic_cast<NetworkViewGraphicsScene *>(scene())->idSpace);
    dialog.exec();
    this->displayName->setPlainText(this->itemObject.property("name").toString());
    this->displayName->adjustSize();
    NetworkViewGraphicsItem::mouseDoubleClickEvent(event);
}
