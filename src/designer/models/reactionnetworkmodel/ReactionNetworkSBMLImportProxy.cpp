#include <QtScript>
#include "ReactionNetworkSBMLImportProxy.h"

ReactionNetworkSBMLImportProxy::ReactionNetworkSBMLImportProxy(ReactionNetworkModel *model) :
    DesignerModelFormatProxyItf(model)
{
    itemPool.append(getEngine()->newObject()); //The root Object
}

ReactionNetworkSBMLImportProxy::~ReactionNetworkSBMLImportProxy()
{
}

QScriptEngine* ReactionNetworkSBMLImportProxy::getEngine()
{
    static QScriptEngine* engine = dynamic_cast<ReactionNetworkModel*>(getModel())->getEngine();
    return engine;
}

typedef ReactionNetworkSBMLImportProxy::modelObjectIndex modelObjectIndex;

modelObjectIndex ReactionNetworkSBMLImportProxy::createModelObject(modelObjectIndex parent, void* data)
{
    QDomElement *domElem = static_cast<QDomElement*>(data);
    if(!domElem)
        return 0;
//    [](int x){ return x*x;}(5);
    QScriptValue newModelObject = getEngine()->newObject();
    itemPool.append(newModelObject);

    printf(domElem->nodeName().toLatin1().data());
    return itemPool.count()-1;
}

void ReactionNetworkSBMLImportProxy::setModelObjectProperty(modelObjectIndex index, QString propertyName, QString value)
{
    printf(propertyName.toLatin1().data());
}

QString ReactionNetworkSBMLImportProxy::getModelObjectProperty(modelObjectIndex index, QString propertyName)
{
    return "";
}

void ReactionNetworkSBMLImportProxy::removeModelObject(modelObjectIndex index)
{

}
