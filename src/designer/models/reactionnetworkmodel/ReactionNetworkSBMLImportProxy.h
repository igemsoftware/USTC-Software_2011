#ifndef REACTIONNETWORKSBMLIMPORTPROXY_H
#define REACTIONNETWORKSBMLIMPORTPROXY_H

#include <QObject>
#include <QtScript>
#include <QtXml>
#include "ReactionNetwork.h"
#include "ReactionNetworkSBMLImportProxy.h"

class ReactionNetworkSBMLImportProxy : public DesignerModelFormatProxyItf
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ReactionNetworkSBMLImportProxy(ReactionNetworkModel *model = 0) :
        DesignerModelFormatProxyItf(model)
    {
        itemPool.append(getEngine()->newObject()); //The root Object
    }

    ~ReactionNetworkSBMLImportProxy()
    {

    }

    QScriptEngine* getEngine()
    {
        static QScriptEngine* engine = dynamic_cast<ReactionNetworkModel*>(getModel())->getEngine();
        return engine;
    }


private:
    QList<QScriptValue> itemPool;

protected:
    QString handler_collectElementTreeAsString(QDomElement* domElem)
    {
        QString text;
        QTextStream textStream(&text);
        domElem->save(textStream, 0);
        return text;
    }
    modelObjectIndex handler_allocateNewIndex(QScriptValue& newModelObject)
    {
        modelObjectIndex newModelObjectIndex = itemPool.count();
        itemPool.append(newModelObject);
        return newModelObjectIndex;
    }

    modelObjectIndex handler_createStandardObject(QDomElement* domElem)
    {
        QScriptValue newModelObject = getEngine()->newObject();
        modelObjectIndex newModelObjectIndex = handler_allocateNewIndex(newModelObject);

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

    modelObjectIndex handler_collectChildObjectsAsArray(QDomElement* domElem)
    {
        QList<modelObjectIndex> childObjectIndexList;
        for(QDomElement childElem = domElem->firstChildElement();
            !childElem.isNull(); childElem = childElem.nextSiblingElement())
        {
            modelObjectIndex itemIndex = createModelObject(0, &childElem);
            if(itemIndex)
                childObjectIndexList.append(itemIndex);
        }

        QScriptValue newObjectList = getEngine()->newArray(childObjectIndexList.count());
        for(qint32 i = 0; i < childObjectIndexList.count(); i++)
            newObjectList.setProperty(i, itemPool[childObjectIndexList[i]]);

        return handler_allocateNewIndex(newObjectList);
    }


public:
    modelObjectIndex createModelObject(modelObjectIndex parent = 0, void* data = 0)
    {
        QDomElement *domElem = static_cast<QDomElement*>(data);
        if(!domElem)
            return 0;

        if(domElem->nodeName()=="notes")
        {
            itemPool[parent].setProperty("*notes*", handler_collectElementTreeAsString(domElem));
            return parent;
        }
        else if(domElem->nodeName()=="annotation")
        {
            itemPool[parent].setProperty("*annotation*", handler_collectElementTreeAsString(domElem));
            return parent;
        }
        else if(domElem->nodeName()=="listOfReactions")
        {
            modelObjectIndex indexOfList = handler_collectChildObjectsAsArray(domElem);
            itemPool[0].setProperty("*reactionlist*", itemPool[indexOfList]);
            return indexOfList;
        }
        else
        {
            return handler_createStandardObject(domElem);
        }
    }


    void setModelObjectProperty(modelObjectIndex index, QString propertyName, QString value)
    {
        printf(propertyName.toLatin1().data());
    }
    QString getModelObjectProperty(modelObjectIndex index, QString propertyName)
    {
        return "";
    }

    void removeModelObject(modelObjectIndex index)
    {

    }


//signals:

//public slots:

};

#endif // REACTIONNETWORKSBMLIMPORTPROXY_H
