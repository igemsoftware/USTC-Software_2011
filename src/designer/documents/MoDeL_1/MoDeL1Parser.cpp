// THIS FILE IS AUTO-GENERATED BY PARSERCOMP.
// PLEASE DON'T EDIT THIS FILE MANUALLY.
// Generate Time: Thu Jul 28 21:32:54 2011


#include "MoDeL1Parser.h"

bool MoDeL1Parser::parse(DesignerModelItf* model, QDomDocument& doc)
{
	QList<parseTask> taskList;
	taskList.push_back(parseTask(QDomElement(), model->getEngine()->globalObject(), 0));
	size_t curTask = 0;
	while(curTask<(size_t)taskList.size())
	{
		switch(taskList[curTask].taskHint)
		{
		case 0:   //
			{
				//defaultAction
				//standardObject
				QDomDocument curElem = doc;
				//create object.
				QScriptValue newItemValue = model->getEngine()->newObject();
				newItemValue.setProperty("*tag*", curElem.nodeName());

				//[append this Item To *subobjects*]
				appendValueToModel(newItemValue, taskList[curTask].taskParent, "/*subobjects*");

				//[write properties]
				for(int attrIndex = 0 ; attrIndex < curElem.attributes().count(); attrIndex++)
				{
					{
						newItemValue.setProperty(  curElem.attributes().item(attrIndex).nodeName(), curElem.attributes().item(attrIndex).nodeValue());
					}
				}
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="MoDeL")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 1));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
			}
			break;
		case 1:   //#object$standardObject~/model
			{
				//standardObject
				QDomElement curElem = taskList[curTask].taskElem;
				//create object.
				QScriptValue newItemValue = model->getEngine()->newObject();
				newItemValue.setProperty("*tag*", curElem.nodeName());

				//[append this Item To *subobjects*]
				appendValueToModel(newItemValue, taskList[curTask].taskParent, "/*subobjects*");

				//[write properties]
				for(int attrIndex = 0 ; attrIndex < curElem.attributes().count(); attrIndex++)
				{
					{
						newItemValue.setProperty(  curElem.attributes().item(attrIndex).nodeName(), curElem.attributes().item(attrIndex).nodeValue());
					}
				}
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="dbInterface")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 2));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				QScriptValue curTargetItem = model->getEngine()->globalObject();
				writeValueToModel(newItemValue, curTargetItem, "/model");
			}
			break;
		case 2:   //#object$ignoreThis
			{
				//skipThis
				QScriptValue newItemValue = taskList[curTask].taskParent;
				QDomElement curElem = taskList[curTask].taskElem;
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="input")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 3));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
			}
			break;
		case 3:   //#object$ignoreThis
			{
				//skipThis
				QScriptValue newItemValue = taskList[curTask].taskParent;
				QDomElement curElem = taskList[curTask].taskElem;
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="listOfParameters")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 4));
					}
					else if(childElem.nodeName()=="listOfRules")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 10));
					}
					else if(childElem.nodeName()=="listOfCompartments")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 14));
					}
					else if(childElem.nodeName()=="listOfSpecies")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 21));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
			}
			break;
		case 4:   //#array$createArray~/model/parameters
			{
				//createArray
				QScriptValue newItemValue;
				newItemValue = model->getEngine()->newArray(0);
				QDomElement curElem = taskList[curTask].taskElem;
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="parameter")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 5));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				QScriptValue curTargetItem = model->getEngine()->globalObject();
				writeValueToModel(newItemValue, curTargetItem, "/model/parameters");
			}
			break;
		case 5:   //#object$standardObject$appendToArray^
			{
				//standardObject
				QDomElement curElem = taskList[curTask].taskElem;
				//create object.
				QScriptValue newItemValue = model->getEngine()->newObject();
				newItemValue.setProperty("*tag*", curElem.nodeName());

				//[append this Item To *subobjects*]
				appendValueToModel(newItemValue, taskList[curTask].taskParent, "/*subobjects*");

				//[write properties]
				for(int attrIndex = 0 ; attrIndex < curElem.attributes().count(); attrIndex++)
				{
					{
						newItemValue.setProperty(  curElem.attributes().item(attrIndex).nodeName(), curElem.attributes().item(attrIndex).nodeValue());
					}
				}
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="id")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 6));
					}
					else if(childElem.nodeName()=="value")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 7));
					}
					else if(childElem.nodeName()=="units")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 8));
					}
					else if(childElem.nodeName()=="constant")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 9));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				appendValueToModel(newItemValue, taskList[curTask].taskParent, "");
			}
			break;
		case 6:   //#value^/id
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/id");
			}
			break;
		case 7:   //#value^/value
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/value");
			}
			break;
		case 8:   //#value^/units
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/units");
			}
			break;
		case 9:   //#value^/constant
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/constant");
			}
			break;
		case 10:   //#array$createArray~/model/rules
			{
				//createArray
				QScriptValue newItemValue;
				newItemValue = model->getEngine()->newArray(0);
				QDomElement curElem = taskList[curTask].taskElem;
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="assignmentRule")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 11));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				QScriptValue curTargetItem = model->getEngine()->globalObject();
				writeValueToModel(newItemValue, curTargetItem, "/model/rules");
			}
			break;
		case 11:   //#object$standardObject$appendToArray^
			{
				//standardObject
				QDomElement curElem = taskList[curTask].taskElem;
				//create object.
				QScriptValue newItemValue = model->getEngine()->newObject();
				newItemValue.setProperty("*tag*", curElem.nodeName());

				//[append this Item To *subobjects*]
				appendValueToModel(newItemValue, taskList[curTask].taskParent, "/*subobjects*");

				//[write properties]
				for(int attrIndex = 0 ; attrIndex < curElem.attributes().count(); attrIndex++)
				{
					{
						newItemValue.setProperty(  curElem.attributes().item(attrIndex).nodeName(), curElem.attributes().item(attrIndex).nodeValue());
					}
				}
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="variable")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 12));
					}
					else if(childElem.nodeName()=="math")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 13));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				appendValueToModel(newItemValue, taskList[curTask].taskParent, "");
			}
			break;
		case 12:   //#value$setProperty^/variable
			{
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/variable");
			}
			break;
		case 13:   //#value$setProperty^/function
			{
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/function");
			}
			break;
		case 14:   //#array$createArray~/model/compartments
			{
				//createArray
				QScriptValue newItemValue;
				newItemValue = model->getEngine()->newArray(0);
				QDomElement curElem = taskList[curTask].taskElem;
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="compartment")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 15));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				QScriptValue curTargetItem = model->getEngine()->globalObject();
				writeValueToModel(newItemValue, curTargetItem, "/model/compartments");
			}
			break;
		case 15:   //#object$standardObject$appendToArray^
			{
				//standardObject
				QDomElement curElem = taskList[curTask].taskElem;
				//create object.
				QScriptValue newItemValue = model->getEngine()->newObject();
				newItemValue.setProperty("*tag*", curElem.nodeName());

				//[append this Item To *subobjects*]
				appendValueToModel(newItemValue, taskList[curTask].taskParent, "/*subobjects*");

				//[write properties]
				for(int attrIndex = 0 ; attrIndex < curElem.attributes().count(); attrIndex++)
				{
					if(curElem.attributes().item(attrIndex).nodeName()=="db")
					{
						taskList.push_back(parseTask(curElem, newItemValue, 16));
					}
					else
					{
						newItemValue.setProperty(  curElem.attributes().item(attrIndex).nodeName(), curElem.attributes().item(attrIndex).nodeValue());
					}
				}
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="id")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 17));
					}
					else if(childElem.nodeName()=="size")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 18));
					}
					else if(childElem.nodeName()=="outside")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 19));
					}
					else if(childElem.nodeName()=="constant")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 20));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				appendValueToModel(newItemValue, taskList[curTask].taskParent, "");
			}
			break;
		case 16:   //#value$getProperty(db)^/*iGame1*/db
			{
				//getProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.attribute("db"));
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*iGame1*/db");
			}
			break;
		case 17:   //#value^/id
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/id");
			}
			break;
		case 18:   //#value^/size
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/size");
			}
			break;
		case 19:   //#value^/outside
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/outside");
			}
			break;
		case 20:   //#value^/constant
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/constant");
			}
			break;
		case 21:   //#array$createArray~/model/species
			{
				//createArray
				QScriptValue newItemValue;
				newItemValue = model->getEngine()->newArray(0);
				QDomElement curElem = taskList[curTask].taskElem;
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="species")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 22));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				QScriptValue curTargetItem = model->getEngine()->globalObject();
				writeValueToModel(newItemValue, curTargetItem, "/model/species");
			}
			break;
		case 22:   //#object$standardObject$appendToArray^
			{
				//standardObject
				QDomElement curElem = taskList[curTask].taskElem;
				//create object.
				QScriptValue newItemValue = model->getEngine()->newObject();
				newItemValue.setProperty("*tag*", curElem.nodeName());

				//[append this Item To *subobjects*]
				appendValueToModel(newItemValue, taskList[curTask].taskParent, "/*subobjects*");

				//[write properties]
				for(int attrIndex = 0 ; attrIndex < curElem.attributes().count(); attrIndex++)
				{
					if(curElem.attributes().item(attrIndex).nodeName()=="db")
					{
						taskList.push_back(parseTask(curElem, newItemValue, 23));
					}
					else
					{
						newItemValue.setProperty(  curElem.attributes().item(attrIndex).nodeName(), curElem.attributes().item(attrIndex).nodeValue());
					}
				}
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="id")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 24));
					}
					else if(childElem.nodeName()=="compartment")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 25));
					}
					else if(childElem.nodeName()=="initialConcentration")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 26));
					}
					else if(childElem.nodeName()=="constant")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 27));
					}
					else if(childElem.nodeName()=="boundaryCondition")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 28));
					}
					else if(childElem.nodeName()=="cnModel")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 29));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				appendValueToModel(newItemValue, taskList[curTask].taskParent, "");
			}
			break;
		case 23:   //#value$getProperty(db)^/*iGame1*/db
			{
				//getProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.attribute("db"));
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*iGame1*/db");
			}
			break;
		case 24:   //#value^/id
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/id");
			}
			break;
		case 25:   //#value^/compartment
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/compartment");
			}
			break;
		case 26:   //#value^/initialConcentration
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/initialConcentration");
			}
			break;
		case 27:   //#value^/constant
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/constant");
			}
			break;
		case 28:   //#value^/boundaryCondition
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/boundaryCondition");
			}
			break;
		case 29:   //#object$standardObject^/*iGame1*
			{
				//standardObject
				QDomElement curElem = taskList[curTask].taskElem;
				//create object.
				QScriptValue newItemValue = model->getEngine()->newObject();
				newItemValue.setProperty("*tag*", curElem.nodeName());

				//[append this Item To *subobjects*]
				appendValueToModel(newItemValue, taskList[curTask].taskParent, "/*subobjects*");

				//[write properties]
				for(int attrIndex = 0 ; attrIndex < curElem.attributes().count(); attrIndex++)
				{
					{
						newItemValue.setProperty(  curElem.attributes().item(attrIndex).nodeName(), curElem.attributes().item(attrIndex).nodeValue());
					}
				}
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="listOfChains")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 30));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*iGame1*");
			}
			break;
		case 30:   //#array$createArray^/chains
			{
				//createArray
				QScriptValue newItemValue;
				newItemValue = model->getEngine()->newArray(0);
				QDomElement curElem = taskList[curTask].taskElem;
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="chain")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 31));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/chains");
			}
			break;
		case 31:   //#object$standardObject$appendToArray^
			{
				//standardObject
				QDomElement curElem = taskList[curTask].taskElem;
				//create object.
				QScriptValue newItemValue = model->getEngine()->newObject();
				newItemValue.setProperty("*tag*", curElem.nodeName());

				//[append this Item To *subobjects*]
				appendValueToModel(newItemValue, taskList[curTask].taskParent, "/*subobjects*");

				//[write properties]
				for(int attrIndex = 0 ; attrIndex < curElem.attributes().count(); attrIndex++)
				{
					{
						newItemValue.setProperty(  curElem.attributes().item(attrIndex).nodeName(), curElem.attributes().item(attrIndex).nodeValue());
					}
				}
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="listOfParts")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 32));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				appendValueToModel(newItemValue, taskList[curTask].taskParent, "");
			}
			break;
		case 32:   //#array$createArray^/parts
			{
				//createArray
				QScriptValue newItemValue;
				newItemValue = model->getEngine()->newArray(0);
				QDomElement curElem = taskList[curTask].taskElem;
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="part")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 33));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/parts");
			}
			break;
		case 33:   //#object$standardObject$appendToArray^
			{
				//standardObject
				QDomElement curElem = taskList[curTask].taskElem;
				//create object.
				QScriptValue newItemValue = model->getEngine()->newObject();
				newItemValue.setProperty("*tag*", curElem.nodeName());

				//[append this Item To *subobjects*]
				appendValueToModel(newItemValue, taskList[curTask].taskParent, "/*subobjects*");

				//[write properties]
				for(int attrIndex = 0 ; attrIndex < curElem.attributes().count(); attrIndex++)
				{
					{
						newItemValue.setProperty(  curElem.attributes().item(attrIndex).nodeName(), curElem.attributes().item(attrIndex).nodeValue());
					}
				}
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="partReference")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 34));
					}
					else if(childElem.nodeName()=="partLabel")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 35));
					}
					else if(childElem.nodeName()=="partType")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 36));
					}
					else if(childElem.nodeName()=="partCategory")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 37));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				appendValueToModel(newItemValue, taskList[curTask].taskParent, "");
			}
			break;
		case 34:   //#value^/reference
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/reference");
			}
			break;
		case 35:   //#value^/label
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/label");
			}
			break;
		case 36:   //#value^/type
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/type");
			}
			break;
		case 37:   //#value^/category
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/category");
			}
			break;
		default:
			{
				//standardObject
				QDomElement curElem = taskList[curTask].taskElem;
				//create object.
				QScriptValue newItemValue = model->getEngine()->newObject();
				newItemValue.setProperty("*tag*", curElem.nodeName());

				//[append this Item To *subobjects*]
				appendValueToModel(newItemValue, taskList[curTask].taskParent, "/*subobjects*");

				//[write properties]
				for(int attrIndex = 0 ; attrIndex < curElem.attributes().count(); attrIndex++)
				{
					{
						newItemValue.setProperty(  curElem.attributes().item(attrIndex).nodeName(), curElem.attributes().item(attrIndex).nodeValue());
					}
				}
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
			}
			break;
		};
		curTask++;
	}
	return true;
}
