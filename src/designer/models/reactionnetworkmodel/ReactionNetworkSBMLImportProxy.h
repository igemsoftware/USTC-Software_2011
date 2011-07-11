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
        getEngine()->globalObject().setProperty("*model*", itemPool[0]);
    }

    ~ReactionNetworkSBMLImportProxy()
    {

    }

    QScriptEngine* getEngine()
    {
        QScriptEngine* engine = dynamic_cast<ReactionNetworkModel*>(getModel())->getEngine();
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

    modelObjectIndex handler_createNoChildObject(QDomElement* domElem)
    {
        QScriptValue newModelObject = getEngine()->newObject();
        modelObjectIndex newModelObjectIndex = handler_allocateNewIndex(newModelObject);

        newModelObject.setProperty("*type*", domElem->nodeName());

        for(int attrIndex = 0 ; attrIndex < domElem->attributes().count(); attrIndex++)
        {
            newModelObject.setProperty(  domElem->attributes().item(attrIndex).nodeName(),
                                         domElem->attributes().item(attrIndex).nodeValue());
        }

        return newModelObjectIndex;
    }

    modelObjectIndex handler_createStandardObject(QDomElement* domElem)
    {
        modelObjectIndex newModelObjectIndex = handler_createNoChildObject(domElem);

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

    modelObjectIndex handler_collectChildObjectAttributeAsArray(QDomElement* domElem, QString childTagName, QString childPropertyName)
    {
        QList<QScriptValue> arrayItemList;
        for(QDomElement childElem = domElem->firstChildElement();
            !childElem.isNull(); childElem = childElem.nextSiblingElement())
        {
            if(childElem.nodeName()==childTagName)
            {
                QString value = childElem.attribute(childPropertyName);
                if(!value.isNull())
                {
                    arrayItemList.append(QScriptValue(value));
                }
            }
        }

        QScriptValue newObjectList = getEngine()->newArray(arrayItemList.count());
        for(qint32 i = 0; i < arrayItemList.count(); i++)
            newObjectList.setProperty(i, arrayItemList[i]);

        return handler_allocateNewIndex(newObjectList);
    }

    modelObjectIndex handler_createFunctionObjectFromMathML(QDomElement* domElem)
    {
        //append
        return 0;
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
        else if(domElem->nodeName()=="listOfCompartments")
        {
            modelObjectIndex indexOfList = handler_collectChildObjectsAsArray(domElem);
            itemPool[0].setProperty("*compartmentlist*", itemPool[indexOfList]);
            return indexOfList;
        }
        else if(domElem->nodeName()=="listOfSpecies")
        {
            modelObjectIndex indexOfList = handler_collectChildObjectsAsArray(domElem);
            itemPool[0].setProperty("*specieslist*", itemPool[indexOfList]);
            return indexOfList;
        }
        else if(domElem->nodeName()=="listOfReactions")
        {
            modelObjectIndex indexOfList = handler_collectChildObjectsAsArray(domElem);
            itemPool[0].setProperty("*reactionlist*", itemPool[indexOfList]);
            return indexOfList;
        }
        else if(domElem->nodeName()==/*Reaction::*/ "listOfReactants")
        {
            modelObjectIndex indexOfList = handler_collectChildObjectAttributeAsArray(domElem, "speciesReference", "species");
            itemPool[parent].setProperty("reactants", itemPool[indexOfList]);
            return indexOfList;
        }
        else if(domElem->nodeName()==/*Reaction::*/ "listOfProducts")
        {
            modelObjectIndex indexOfList = handler_collectChildObjectAttributeAsArray(domElem, "speciesReference", "species");
            itemPool[parent].setProperty("products", itemPool[indexOfList]);
            return indexOfList;
        }
        else if(domElem->nodeName()==/*Reaction::*/ "listOfModifiers")
        {
            modelObjectIndex indexOfList = handler_collectChildObjectAttributeAsArray(domElem, "modifierSpeciesReference", "species");
            itemPool[parent].setProperty("modifier", itemPool[indexOfList]);
            return indexOfList;
        }
        else
        {
            return handler_createStandardObject(domElem);
        }
    }


    void setModelObjectProperty(modelObjectIndex index, QString propertyName, QString value)
    {
        itemPool[index].setProperty(propertyName, value);
//        printf(propertyName.toLatin1().data());
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
