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

    struct handlers
    {
        static QString collectChildrenAsString(QDomElement& elem)
        {
            return "";
        }
    };
    if(domElem->nodeName()=="notes")
    {
        QString text;
        QTextStream textStream(&text);
        domElem->save(textStream, 0);

        itemPool[parent].setProperty("*notes*", text);

        return parent;
    }
    else if(domElem->nodeName()=="annotation")
    {
        QString text;
        QTextStream textStream(&text);
        domElem->save(textStream, 0);

        itemPool[parent].setProperty("*annotation*", domElem->toText().data());
        return parent;
    }
    else
    {
        QScriptValue newModelObject = getEngine()->newObject();
        modelObjectIndex newModelObjectIndex = itemPool.count();
        itemPool.append(newModelObject);

        newModelObject.setProperty("*name*", domElem->nodeName());

        for(int attrIndex = 0 ; attrIndex < domElem->attributes().count(); attrIndex++)
        {
            newModelObject.setProperty(  domElem->attributes().item(attrIndex).nodeName(),
                                         domElem->attributes().item(attrIndex).nodeValue());
        }

        for(QDomElement childElem = domElem->firstChildElement();
            !childElem.isNull(); childElem = childElem.nextSiblingElement())
        {
            createModelObject(newModelObjectIndex, &childElem);
        }

        return newModelObjectIndex;
    }
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
