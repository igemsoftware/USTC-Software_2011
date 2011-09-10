// THIS FILE IS AUTO-GENERATED BY PARSERCOMP.
// PLEASE DON'T EDIT THIS FILE MANUALLY.
// Generate Time: Wed Aug 03 00:11:03 2011


#include "RSBPMLParser.h"

bool RSBPMLParser::parse(DesignerModelComponent* model, QDomDocument& doc)
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
					if(childElem.nodeName()=="rsbpml")
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
		case 1:   //
			{
				//defaultAction
				//standardObject
				QDomElement curElem = taskList[curTask].taskElem;
				//create object.
				QScriptValue newItemValue = model->getEngine()->newObject();

				newItemValue.setProperty("*tag*", curElem.nodeName());
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
					if(childElem.nodeName()=="part_list")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 2));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
			}
			break;
		case 2:   //#array$createArray~/model
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
						taskList.push_back(parseTask(childElem, newItemValue, 3));
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
		case 3:   //#object$markAsModel$standardObject$appendToArray^
			{
				//standardObject
				QDomElement curElem = taskList[curTask].taskElem;
				//create object.
				QScriptValue newItemValue = model->getEngine()->newObject();

				newItemValue.setProperty("*tag*", curElem.nodeName());
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
					if(childElem.nodeName()=="part_id")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 4));
					}
					else if(childElem.nodeName()=="part_name")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 5));
					}
					else if(childElem.nodeName()=="part_short_name")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 6));
					}
					else if(childElem.nodeName()=="part_short_desc")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 7));
					}
					else if(childElem.nodeName()=="part_type")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 8));
					}
					else if(childElem.nodeName()=="part_status")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 9));
					}
					else if(childElem.nodeName()=="part_results")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 10));
					}
					else if(childElem.nodeName()=="part_nickname")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 11));
					}
					else if(childElem.nodeName()=="part_rating")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 12));
					}
					else if(childElem.nodeName()=="part_url")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 13));
					}
					else if(childElem.nodeName()=="part_entered")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 14));
					}
					else if(childElem.nodeName()=="part_author")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 15));
					}
					else if(childElem.nodeName()=="best_quality")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 16));
					}
					else if(childElem.nodeName()=="deep_subparts")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 17));
					}
					else if(childElem.nodeName()=="specified_subparts")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 18));
					}
					else if(childElem.nodeName()=="specified_subscars")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 19));
					}
					else if(childElem.nodeName()=="sequences")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 20));
					}
					else if(childElem.nodeName()=="features")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 22));
					}
					else if(childElem.nodeName()=="parameters")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 30));
					}
					else if(childElem.nodeName()=="categories")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 40));
					}
					else if(childElem.nodeName()=="twins")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 42));
					}
					else if(childElem.nodeName()=="samples")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 44));
					}
					else if(childElem.nodeName()=="references")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 45));
					}
					else if(childElem.nodeName()=="groups")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 46));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				appendValueToModel(newItemValue, taskList[curTask].taskParent, "");
			}
			break;
		case 4:   //#value^/*partsregistry.org*/part_id
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/part_id");
			}
			break;
		case 5:   //#value^/*partsregistry.org*/part_name
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/part_name");
			}
			break;
		case 6:   //#value^/*partsregistry.org*/part_short_name
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/part_short_name");
			}
			break;
		case 7:   //#value^/*partsregistry.org*/part_short_desc
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/part_short_desc");
			}
			break;
		case 8:   //#value^/*partsregistry.org*/part_type
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/part_type");
			}
			break;
		case 9:   //#value^/*partsregistry.org*/part_status
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/part_status");
			}
			break;
		case 10:   //#value^/*partsregistry.org*/part_results
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/part_results");
			}
			break;
		case 11:   //#value^/*partsregistry.org*/part_short_desc
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/part_short_desc");
			}
			break;
		case 12:   //#value^/*partsregistry.org*/part_rating
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/part_rating");
			}
			break;
		case 13:   //#value^/*partsregistry.org*/part_url
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/part_url");
			}
			break;
		case 14:   //#value^/*partsregistry.org*/part_entered
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/part_entered");
			}
			break;
		case 15:   //#value^/*partsregistry.org*/part_author
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/part_author");
			}
			break;
		case 16:   //#value^/*partsregistry.org*/best_quailty
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/best_quailty");
			}
			break;
		case 17:   //#value^/*partsregistry.org*/deep_subparts
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/deep_subparts");
			}
			break;
		case 18:   //#value^/*partsregistry.org*/specified_subparts
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/specified_subparts");
			}
			break;
		case 19:   //#value^/*partsregistry.org*/specified_subscars
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/specified_subscars");
			}
			break;
		case 20:   //#value$ignoreThis
			{
				//skipThis
				QScriptValue newItemValue = taskList[curTask].taskParent;
				QDomElement curElem = taskList[curTask].taskElem;
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="seq_data")
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
		case 21:   //#value^/partsequence
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/partsequence");
			}
			break;
		case 22:   //#array$createArray^/partfeatures
			{
				//createArray
				QScriptValue newItemValue;
				newItemValue = model->getEngine()->newArray(0);
				QDomElement curElem = taskList[curTask].taskElem;
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="feature")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 23));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/partfeatures");
			}
			break;
		case 23:   //#object$standardObject$appendToArray^
			{
				//standardObject
				QDomElement curElem = taskList[curTask].taskElem;
				//create object.
				QScriptValue newItemValue = model->getEngine()->newObject();

				newItemValue.setProperty("*tag*", curElem.nodeName());
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
						taskList.push_back(parseTask(childElem, newItemValue, 24));
					}
					else if(childElem.nodeName()=="title")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 25));
					}
					else if(childElem.nodeName()=="type")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 26));
					}
					else if(childElem.nodeName()=="direction")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 27));
					}
					else if(childElem.nodeName()=="startpos")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 28));
					}
					else if(childElem.nodeName()=="endpos")
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
		case 24:   //#value^/featureid
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/featureid");
			}
			break;
		case 25:   //#value^/featuretitle
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/featuretitle");
			}
			break;
		case 26:   //#value^/featuretype
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/featuretype");
			}
			break;
		case 27:   //#value^/featuredirection
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/featuredirection");
			}
			break;
		case 28:   //#value^/featurestartpos
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/featurestartpos");
			}
			break;
		case 29:   //#value^/featureendpos
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/featureendpos");
			}
			break;
		case 30:   //#array$createArray^/*partsregistry.org*/part_parameters
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
						taskList.push_back(parseTask(childElem, newItemValue, 31));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/part_parameters");
			}
			break;
		case 31:   //#object$standardObject$appendToArray^
			{
				//standardObject
				QDomElement curElem = taskList[curTask].taskElem;
				//create object.
				QScriptValue newItemValue = model->getEngine()->newObject();

				newItemValue.setProperty("*tag*", curElem.nodeName());
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
					if(childElem.nodeName()=="name")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 32));
					}
					else if(childElem.nodeName()=="value")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 33));
					}
					else if(childElem.nodeName()=="units")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 34));
					}
					else if(childElem.nodeName()=="url")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 35));
					}
					else if(childElem.nodeName()=="id")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 36));
					}
					else if(childElem.nodeName()=="m_date")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 37));
					}
					else if(childElem.nodeName()=="user_id")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 38));
					}
					else if(childElem.nodeName()=="user_name")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 39));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				appendValueToModel(newItemValue, taskList[curTask].taskParent, "");
			}
			break;
		case 32:   //#value^/parameter_name
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/parameter_name");
			}
			break;
		case 33:   //#value^/parameter_value
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/parameter_value");
			}
			break;
		case 34:   //#value^/parameter_units
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/parameter_units");
			}
			break;
		case 35:   //#value^/parameter_url
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/parameter_url");
			}
			break;
		case 36:   //#value^/parameter_id
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/parameter_id");
			}
			break;
		case 37:   //#value^/paramter_m_date
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/paramter_m_date");
			}
			break;
		case 38:   //#value^/parameter_user_id
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/parameter_user_id");
			}
			break;
		case 39:   //#value^/parameter_user_name
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/parameter_user_name");
			}
			break;
		case 40:   //#array$createArray^/*partsregistry.org*/categories
			{
				//createArray
				QScriptValue newItemValue;
				newItemValue = model->getEngine()->newArray(0);
				QDomElement curElem = taskList[curTask].taskElem;
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="category")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 41));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/categories");
			}
			break;
		case 41:   //#value$setProperty$appendToArray^
			{
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				appendValueToModel(newItemValue, taskList[curTask].taskParent, "");
			}
			break;
		case 42:   //#array$createArray^/*partsregistry.org*/twins
			{
				//createArray
				QScriptValue newItemValue;
				newItemValue = model->getEngine()->newArray(0);
				QDomElement curElem = taskList[curTask].taskElem;
				//[write children objects]
				for(QDomElement childElem = curElem.firstChildElement();
					!childElem.isNull(); childElem = childElem.nextSiblingElement())
				{
					if(childElem.nodeName()=="twin")
					{
						taskList.push_back(parseTask(childElem, newItemValue, 43));
					}
					else
					{
						taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));
					}
				}
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/twins");
			}
			break;
		case 43:   //#value$setProperty$appendToArray^
			{
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				appendValueToModel(newItemValue, taskList[curTask].taskParent, "");
			}
			break;
		case 44:   //#value^/*partsregistry.org*/samples
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/samples");
			}
			break;
		case 45:   //#value^/*partsregistry.org*/references
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/references");
			}
			break;
		case 46:   //#value^/*partsregistry.org*/groups
			{
				//defaultAction
				//setProperty
				QScriptValue newItemValue;
				newItemValue = QScriptValue(taskList[curTask].taskElem.text());
				QScriptValue curTargetItem = taskList[curTask].taskParent;
				writeValueToModel(newItemValue, curTargetItem, "/*partsregistry.org*/groups");
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
