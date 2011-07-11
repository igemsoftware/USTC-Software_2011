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

    void handler_ensureTargetPropertyIsArray(QScriptValue object, QString propertyName)
    {
        if(!object.property(propertyName).isArray())
        {
            object.setProperty(propertyName, getEngine()->newArray(0));
        }
    }

    void handler_appendArrayObjectToArrayObject(QScriptValue srcObject, QScriptValue destObject)
    {
        int srcLength = srcObject.property("length").toInt32();
        int destLength = destObject.property("length").toInt32();
        for(int i = 0; i < srcLength; i++)
        {
            destObject.setProperty(i+destLength, srcObject.property(i));
        }
        destObject.setProperty("length", srcLength+destLength);
    }

    QScriptValue handler_createFunctionObjectFromMathMLItem(QDomElement* domElem)
    {
        if(domElem->nodeName()=="ci")
        {
            return QScriptValue(QString("'")+domElem->nodeValue().toUtf8());
        }
        else if(domElem->nodeName()=="cn")
        {
            if(domElem->attribute("type")=="integer")
            {
                return QScriptValue(domElem->nodeValue().toInt());
            }
            else if(domElem->attribute("type")=="real")
            {
                return QScriptValue(domElem->nodeValue().toDouble());
            }
        }
        else if(domElem->nodeName()=="apply")
        {
            QList<QScriptValue> valueList;
            for(QDomElement childElem = domElem->firstChildElement(); !childElem.isNull(); childElem=childElem.nextSiblingElement())
            {
                valueList.push_back(handler_createFunctionObjectFromMathMLItem(&childElem));
            }

            QScriptValue newArray = getEngine()->newArray(valueList.count());
            for(int i=0;i<valueList.count();i++)
            {
                newArray.setProperty(i, valueList[i]);
            }
            return newArray;
        }

        return QScriptValue(QString(domElem->nodeValue().toUtf8()));

    }

    modelObjectIndex handler_createFunctionObjectFromMathML(QDomElement* domElem)
    {
        QDomElement childElement = domElem->firstChildElement();
        QScriptValue functionObject = handler_createFunctionObjectFromMathMLItem(&childElement);

        return handler_allocateNewIndex(functionObject);;
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
        else if(domElem->nodeName()==/*Reaction::kineticLaw*/ "math")
        {
            itemPool[parent].setProperty("math", itemPool[handler_createFunctionObjectFromMathML(domElem)]);
            return parent;
        }
        else if(domElem->nodeName()==/*Reaction::kineticLaw*/ "listOfParameters")
        {
            modelObjectIndex indexOfList = handler_collectChildObjectsAsArray(domElem);
            handler_ensureTargetPropertyIsArray(itemPool[0], "*parameterlist*");
            handler_appendArrayObjectToArrayObject(itemPool[indexOfList], itemPool[0].property("*parameterlist*"));
            return 0;
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
