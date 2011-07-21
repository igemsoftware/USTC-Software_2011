// THIS FILE IS AUTO-GENERATED BY PARSERCOMP.
// PLEASE DON'T EDIT THIS FILE MANUALLY.
// Generate Time: Thu Jul 21 14:53:09 2011


#include "SBOLParser.h"

bool SBOLParser::parse(DesignerModelItf* model, QDomDocument& doc)
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
					if(childElem.nodeName()=="rdf:RDF")
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
		case 1:   //#array$createArray~/model
			{
				//createArray
				QScriptValue newItemValue;
				newItemValue = model->getEngine()->newArray(0);
				QDomElement curElem = taskList[curTask].taskElem;
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="rdf:Description")
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
		case 2:   //#object$markAsModel$standardObject$appendToArray~/model
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
					if(childElem.nodeName()=="rdf:type")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 3));
					}
					else if(childElem.nodeName()=="shortDescription")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 4));
					}
					else if(childElem.nodeName()=="author")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 5));
					}
					else if(childElem.nodeName()=="name")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 6));
					}
					else if(childElem.nodeName()=="dnaSequence")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 7));
					}
					else if(childElem.nodeName()=="date")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 8));
					}
					else if(childElem.nodeName()=="longDescription")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 9));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				appendValueToModel(newItemValue, model->getEngine()->globalObject(), "/model");
			}
			break;
		case 3:   //#value$getProperty(rdf:resource)^/*sbol*/rdf_type_uri
			{
				//getProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.attribute("rdf:resource").text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*sbol*/rdf_type_uri");
			}
			break;
		case 4:   //#value^/*sbol*/shortDescription
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*sbol*/shortDescription");
			}
			break;
		case 5:   //#value^/*sbol*/author
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*sbol*/author");
			}
			break;
		case 6:   //#value^/*sbol*/name
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*sbol*/name");
			}
			break;
		case 7:   //#value^/partsequence
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/partsequence");
			}
			break;
		case 8:   //#value^/*sbol*/date
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*sbol*/date");
			}
			break;
		case 9:   //#value^/*sbol*/longDescription
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*sbol*/longDescription");
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
