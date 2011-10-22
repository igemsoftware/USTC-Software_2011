#include "NetworkViewGraphicsSceneNodeReaction.h"
#include "models/common/ModelSymbol.h"
#include "NetworkViewReactionEditor.h"

NetworkViewGraphicsSceneNodeReaction::NetworkViewGraphicsSceneNodeReaction(QScriptValue value, QGraphicsItem *parent, bool isParentContainer)
    :NetworkViewGraphicsSceneNode( parent,value, QObject::tr(":/designer/assemblyview/icon_mol.png") , QObject::tr(":/designer/assemblyview/icon_mol_selected.png") ,isParentContainer )
{
    Type="reaction";
}

void NetworkViewGraphicsSceneNodeReaction::refreshScriptValue()
{
    QScriptValueList reactants;
    QScriptValueList products;
    QScriptValueList modifiers;
    QScriptEngine *engine;
    QScriptValue newvalue;

    engine=dynamic_cast<NetworkViewGraphicsScene *>(scene())->model->getEngine();
    foreach(NetworkViewGraphicsSceneEdge *edge,edgeList)
    {
        newvalue=engine->newObject();
        newvalue.setProperty("*tag*","speciesReference");
        if(edge->edgeNode1==this)
        {
            newvalue.setProperty("species",edge->edgeNode2->itemObject.property("id"));
            if(edge->edgeType==NetworkViewGraphicsSceneEdge::BidirectedEdge)
                reactants.push_back(newvalue);
            products.push_back(newvalue);
        }
        else if(edge->edgeNode2==this)
        {
            newvalue.setProperty("species",edge->edgeNode1->itemObject.property("id"));
            if(edge->edgeType==NetworkViewGraphicsSceneEdge::BidirectedEdge)
                products.push_back(newvalue);
            reactants.push_back(newvalue);
        }
    }
    foreach(NetworkViewGraphicsSceneModification *mod,modList)
    {
        newvalue=engine->newObject();
        newvalue.setProperty("*tag*","modiifierSpeciesReference");
        newvalue.setProperty("species",mod->edgeNode1->itemObject.property("id"));
        modifiers.push_back(newvalue);
    }

    this->itemObject.setProperty( "reactants" , convertModelTypeToScriptValue(engine,reactants));
    this->itemObject.setProperty( "products" , convertModelTypeToScriptValue(engine,products));
    this->itemObject.setProperty("modifiers" , convertModelTypeToScriptValue(engine,modifiers));
}

void NetworkViewGraphicsSceneNodeReaction::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    NetworkViewReactionEditor dialog(itemObject,dynamic_cast<NetworkViewGraphicsScene *>(scene())->idSpace);
    dialog.exec();    
    NetworkViewGraphicsItem::mouseDoubleClickEvent(event);
}
