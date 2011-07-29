#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <sstream>
#include <cassert>
#include <map>
using namespace std;

void showlogo()
{
	cerr<<"Biology xml standard parser generator v1"<<endl;
	cerr<<"by CrLF0710"<<endl;
	cerr<<"----------------------------------"<<endl;
}

void usage (char* cmdName)
{
	cerr<<"Usage: " <<cmdName <<" <input-file> -o<output-file>"<<endl;
	cerr<<endl;
}
/*
class stringx : public string
{
public:
	stringx() : string(){}
	stringx(const string& rhs) : string(rhs){}

	bool startWith(string rhs)
	{
		return substr(0, rhs.length)==rhs;
	}

	bool endWith(string rhs)
	{
		return (length()>=rhs.length() && substr(length()-rhs.length())==rhs);
	}
	stringx& operator = (const string& rhs)
	{
		return string::operator=(rhs);
	}
}
*/

bool startWith(string str1, string str2)
{
	return str1.substr(0, str2.length())==str2;
}

bool endWith(string str1, string str2)
{

	return (str1.length()>=str2.length()
		&& str1.substr(str1.length()-str2.length())==str2);
}

string result_split_path(string path, size_t i)
{
	char buffer[4][256];
	_splitpath(path.c_str(),
		buffer[0],
		buffer[1],
		buffer[2],
		buffer[3]);
	return buffer[i];

}

string result_include_once_macro_name(string path)
{
	char buffer[256];
	strcpy(buffer, result_split_path(path,2).c_str());
	strcat(buffer, result_split_path(path,3).c_str());

	//    splitpath_s(path, NULL, 0, NULL, 0, buffer, 256, NULL, 0);
	for(int i=0;i<strlen(buffer);i++)
	{
		if(!isalpha(buffer[i])) buffer[i]='_';
	}


	strupr(buffer);


	return buffer;
}

string result_current_time()
{
	time_t curtime;
	time( &curtime );
	return ctime( &curtime );
}

string trim_left(string str)
{
	size_t pos = str.find_first_not_of("\r\n\t ");
	if(pos==string::npos)
		return "";
	return str.substr(pos);
}

string trim_right(string str)
{
	size_t pos = str.find_last_not_of("\r\n\t ");
	if(pos==string::npos)
		return "";
	else
	{
		string newstr = str;
		newstr.erase(str.find_last_not_of("\r\n\t ")+1);
		return newstr;
	}
}

string trim(string str)
{
	return trim_right(trim_left(str));
}



	struct state_rule_struct
	{
		int targetState;
		string childName;
		string attributeName;
		string assertionString;

		state_rule_struct(){};
		state_rule_struct(string _child, string _attrib, string _assert, int _target)
			: childName(_child), attributeName(_attrib), assertionString(_assert), targetState(_target) {}
	};

	struct state_struct
	{
		int state_id;
		string rule;
		vector<state_rule_struct> transform_rules;

		static map<int, state_struct*> registry;

		state_struct()
		{
			static int id = 0;
			state_id = id++;
		}
	};
	map<int, state_struct*> state_struct::registry;

	struct state_map_class: public map<string, state_struct>
	{
		static void split_rule_lhs_string(string lhs, string& nodeNameSubstring, string& attrNameSubstring, string& assertionSubstring)
		{
			size_t attrStart = lhs.find_first_of("@?");
			size_t assertionStart;
			if(attrStart!=string::npos)
			{
				if(lhs[attrStart]=='@')
				{
					assertionStart = lhs.find('?', attrStart+1);
				}
				else
				{
					assertionStart = attrStart;
					attrStart = string::npos;
				}
			}
			else
			{
				assertionStart=string::npos;
			}
			if(attrStart!=string::npos)
			{
				if(assertionStart!=string::npos)
				{
					nodeNameSubstring = lhs.substr(0, attrStart);
					attrNameSubstring = lhs.substr(attrStart+1, assertionStart-attrStart-1);
					assertionSubstring = lhs.substr(assertionStart+1);
				}
				else
				{
					nodeNameSubstring = lhs.substr(0, attrStart);
					attrNameSubstring = lhs.substr(attrStart+1);
					assertionSubstring = "";
				}
			}
			else
			{
				if(assertionStart!=string::npos)
				{
					nodeNameSubstring = lhs.substr(0, assertionStart);
					attrNameSubstring = "";
					assertionSubstring = lhs.substr(assertionStart+1);
				}
				else
				{
					nodeNameSubstring = lhs.substr(0, assertionStart);
					attrNameSubstring = "";
					assertionSubstring = "";
				}
			}

		}
		
		state_struct& retrieve_state_struct_for_node(string nodeNameSubstring)
		{
			size_t splitPos = nodeNameSubstring.find_last_of('/');
			state_struct& parentState = (splitPos==string::npos ? *state_struct::registry[0] : retrieve_state_struct_for_node(nodeNameSubstring.substr(0, splitPos)));
			state_struct& thisState = (*this)[nodeNameSubstring];

			bool bConnectionEstablished = false;
			for(int i=0;i<parentState.transform_rules.size();i++)
			{
				if(parentState.transform_rules[i].childName==nodeNameSubstring.substr(splitPos+1))
				{
					bConnectionEstablished = true;
					break;
				}
			}
			if(!bConnectionEstablished)
			{
				parentState.transform_rules.push_back(state_rule_struct(nodeNameSubstring.substr(splitPos+1), "", "", thisState.state_id));
			}
			state_struct::registry[thisState.state_id]=&thisState;
			return thisState;
		}

		void write_rule(string nodeNameSubstring, string attrNameSubstring, string assertionSubstring, string rhs)
		{
			state_struct& nodeStruct = retrieve_state_struct_for_node(nodeNameSubstring);
			if(!attrNameSubstring.length()&&!assertionSubstring.length())
			{
				nodeStruct.rule = rhs;
			}
			else
			{
				bool bConnectionEstablished = false;
				for(int i=0;i<nodeStruct.transform_rules.size();i++)
				{
					if(nodeStruct.transform_rules[i].attributeName==attrNameSubstring
						&& nodeStruct.transform_rules[i].assertionString==assertionSubstring)
					{
						bConnectionEstablished = true;
						break;
					}
				}
				if(!bConnectionEstablished)
				{
					state_struct& newState = *new state_struct();
					newState.rule = rhs;
					state_struct::registry[newState.state_id]=&newState;
					nodeStruct.transform_rules.push_back(state_rule_struct("", attrNameSubstring, assertionSubstring, newState.state_id));
				}
			}
		}
	} state_map;

void extract_rule(string rhs, string& resultType, vector<string>& commands, string& targetPos)
{
	int left_edge = rhs.find_first_of("#$~^");
	int right_edge;
	if(left_edge!=string::npos)
	{
		while((right_edge = rhs.find_first_of("#$~^", left_edge+1))!=string::npos)
		{
			string item = rhs.substr(left_edge, right_edge-left_edge);
			if(startWith(item, "#"))
			{
				resultType = item.substr(1);
			}
			else if(startWith(item, "$"))
			{
				commands.push_back(item.substr(1));
			}
			else
			{
				targetPos = item;
			}
			left_edge = right_edge;
		}
		string item = rhs.substr(left_edge);
		if(startWith(item, "#"))
		{
			resultType = item.substr(1);
		}
		else if(startWith(item, "$"))
		{
			commands.push_back(item.substr(1));
		}
		else
		{
			targetPos = item;
		}
	}

}

string generateHeaderName(string fileName)
{
	return result_split_path(fileName, 2) + ".h";
}

string generateClassName(string fileName)
{
	string className = result_split_path(fileName, 2);
	for(int i=0;i<className.length();i++)
		if(!isalnum(className[i]))
			className[i]='_';
	return className;
}

string generateAssertionClause(string assertionString)
{
	vector<string> assertionList;
	int splitleftPos = 0;
	while(splitleftPos!=string::npos)
	{
		int splitrightPos = assertionString.find(splitleftPos+1, '?');
		string item = trim(assertionString.substr(splitleftPos,splitrightPos==string::npos ? string::npos : splitrightPos-splitleftPos));
		if(item.size()) assertionList.push_back(item);

		splitleftPos = splitrightPos;
	}
	string resultString;
	for(int i=0;i<assertionList.size();i++)
	{
		resultString+="&&(";

		{
			int equalPos = assertionList[i].find("==");
			string targetString = assertionList[i].substr(0, equalPos);
			if(startWith(targetString, "^@"))
			{
				resultString+="curElem.attribute(\"";
				resultString+=targetString.substr(2);
				resultString+="\")";
				resultString+=assertionList[i].substr(equalPos);
			}
		}
		resultString+=")";
	}
	return resultString;
}

void generateWriteToParentStub(ostream& fout)
{
	fout<<"\t\t\t\t"<<"//[append this Item To *subobjects*]"<<endl;
	fout<<"\t\t\t\t"<<"appendValueToModel(newItemValue, taskList[curTask].taskParent, \"/*subobjects*\");"<<endl;
	fout<<endl;	
}

void generateWriteAttributesStub(ostream& fout, int i/*hint*/, int indentLength)
{
	string indent = "";
	{
		for(int i=0;i<indentLength;i++)
		{
			indent+="\t";
		}
	}

	fout<<indent<<"//[write properties]"<<endl;
	fout<<indent<<"for(int attrIndex = 0 ; attrIndex < curElem.attributes().count(); attrIndex++)"<<endl;
	fout<<indent<<"{"<<endl;
	if(i>=0)
	{
		int childAttribRulesWritten = 0;
		for(int k=0;k<state_struct::registry[i]->transform_rules.size();k++)
		{
			if(!state_struct::registry[i]->transform_rules[k].childName.length())
			{
				fout<<indent<<"\t"<< (childAttribRulesWritten ? "else " : "")<< "if(curElem.attributes().item(attrIndex).nodeName()==\""<<state_struct::registry[i]->transform_rules[k].attributeName<<"\""<<generateAssertionClause(state_struct::registry[i]->transform_rules[k].assertionString)<<")"<<endl;
				fout<<indent<<"\t"<<"{"<<endl;
				fout<<indent<<"\t\t"<<"taskList.push_back(parseTask(curElem, newItemValue, "<<state_struct::registry[i]->transform_rules[k].targetState<<"));"<<endl;
				fout<<indent<<"\t"<<"}"<<endl;
				childAttribRulesWritten++;
			}
		}

		if(childAttribRulesWritten) fout<<indent<<"\t"<<"else"<<endl;
	}
	fout<<indent<<"\t"<<"{"<<endl;
	fout<<indent<<"\t\t"<<"newItemValue.setProperty(  curElem.attributes().item(attrIndex).nodeName(), curElem.attributes().item(attrIndex).nodeValue());"<<endl;
	fout<<indent<<"\t"<<"}"<<endl;

	fout<<indent<<"}"<<endl;

}

void generateWriteChildrenObjectsStub(ostream& fout, int i/*hint*/, int indentLength)
{
	string indent = "";
	{
		for(int i=0;i<indentLength;i++)
		{
			indent+="\t";
		}
	}

	fout<<indent<<"//[write children objects]"<<endl;
	fout<<indent<<"for(QDomElement childElem = curElem.firstChildElement();"<<endl;

	fout<<indent<<"\t"<<"!childElem.isNull(); childElem = childElem.nextSiblingElement())"<<endl;
	fout<<indent<<"{"<<endl;
	if(i>=0)
	{
		int childElemRulesWritten = 0;
		for(int k=0;k<state_struct::registry[i]->transform_rules.size();k++)
		{
			if(state_struct::registry[i]->transform_rules[k].childName.length())
			{
				fout<<indent<<"\t"<< (childElemRulesWritten ? "else " : "")<< "if(childElem.nodeName()==\""<<state_struct::registry[i]->transform_rules[k].childName<<"\""<<generateAssertionClause(state_struct::registry[i]->transform_rules[k].assertionString)<<")"<<endl;
				fout<<indent<<"\t"<<"{"<<endl;
				fout<<indent<<"\t\t"<<"taskList.push_back(parseTask(childElem, newItemValue, "<<state_struct::registry[i]->transform_rules[k].targetState<<"));"<<endl;
				fout<<indent<<"\t"<<"}"<<endl;
				childElemRulesWritten++;
			}
		}
		if(childElemRulesWritten) fout<<indent<<"\t"<<"else"<<endl;
	}
	fout<<indent<<"\t"<<"{"<<endl;
	fout<<indent<<"\t\t"<<"taskList.push_back(parseTask(childElem, newItemValue, (size_t)-1));"<<endl;
	fout<<indent<<"\t"<<"}"<<endl;

	fout<<indent<<"}"<<endl;

}


int parse(const char* _inputfile, const char* _outputfile)
{
	string inputfile = _inputfile;
	string outputfile = _outputfile;
	if(!endWith(_outputfile, ".cpp"))
		outputfile+=".cpp";

	string className = generateClassName(_outputfile);
	string headerName = generateHeaderName(outputfile);


	ifstream fin(inputfile.c_str());
	ofstream fout(outputfile.c_str());

	string line;
	if(!fin||!fout)
	{
		cerr<<"Can't open file"<<endl;   return 1;
	}

	vector<string> lhs_rule;
	vector<string> rhs_rule;

	while(getline(fin, line))
	{
		// trim it.
		line=trim(line.substr(0, line.find(";;") ));

		int arrowPos = line.find("=>");
		int arrow2Pos = line.find("<=");
		if(arrowPos==string::npos)
		{
			if(line!="")
			{
				cerr << "Found garbage: " << line<< endl;
			}
		}
		else
		{
			lhs_rule.push_back(trim(line.substr(0, arrowPos)));
			if(arrow2Pos==string::npos)
			{
				rhs_rule.push_back(trim(line.substr(arrowPos + 2)));
			}
			else
			{
				rhs_rule.push_back(trim(line.substr(arrowPos + 2, arrow2Pos - arrowPos - 2)));
			}
		}
	}

	
	state_struct& newState = *new state_struct();
	assert(newState.state_id==0);
	state_struct::registry[newState.state_id]=&newState;

	for(int i =0;i<lhs_rule.size();i++)
	{
		string lhs = lhs_rule[i];
		string nodeNameSubstring, attrNameSubstring, assertionSubstring;
		state_map_class::split_rule_lhs_string(lhs, nodeNameSubstring, attrNameSubstring, assertionSubstring);

		state_map.write_rule(nodeNameSubstring, attrNameSubstring, assertionSubstring, rhs_rule[i]);
	}

	for(int i=0;i<state_struct::registry.size();i++)
	{
		state_struct* item = state_struct::registry[i];
		if(item&&item->state_id==i)
		{
			cerr<<i<<". "<<item->state_id<<" rule:"<<item->rule<<endl;
		}
	}

	//write header
	{
		fout<<"// THIS FILE IS AUTO-GENERATED BY PARSERCOMP."<<endl;
		fout<<"// PLEASE DON'T EDIT THIS FILE MANUALLY."<<endl;
		fout<<"// Generate Time: "<<result_current_time()<<endl;
		fout<<endl;
	}

	//write include
	{
		fout<<"#include \""<<headerName << "\"" <<endl;
		fout<<endl;
	}

	{
		fout<< "bool " << className << "::parse(DesignerModelItf* model, QDomDocument& doc)"<<endl;
		fout<< "{" <<endl;
//		fout<< "\t" << "struct parseTask"<<endl;
//		fout<< "\t" << "{"<<endl;
//		fout<< "\t\t" << "QDomElement taskElem;"<<endl;
//		fout<< "\t\t" << "QScriptValue taskParent;" <<endl;
//		fout<< "\t\t" << "size_t       taskHint;" <<endl;
//		fout<< "\t\t" << "parseTask(QDomElement _elem, QScriptValue _parent, size_t _hint):taskElem(_elem), taskParent(_parent), taskHint(_hint){}" <<endl;
//		fout<< "\t" << "};" <<endl;
//		fout<<endl;

		fout<< "\t" << "QList<parseTask> taskList;" <<endl;
		fout<< "\t" << "taskList.push_back(parseTask(QDomElement(), model->getEngine()->globalObject(), 0));" <<endl;
	
		fout<< "\t" << "size_t curTask = 0;" <<endl;
		fout<< "\t" << "while(curTask<(size_t)taskList.size())" <<endl;
		fout<< "\t" << "{"<<endl;

		fout<< "\t\t" << "switch(taskList[curTask].taskHint)" <<endl;
		fout<< "\t\t" << "{"<<endl;

		for(int i=0;i<state_struct::registry.size();i++)
		{
			fout<< "\t\t" << "case "<<i<<":   "<<"//"<<state_struct::registry[i]->rule<<endl;
			fout<< "\t\t\t" << "{" <<endl;
			{
				string resultType;
				vector<string> commands;
				string targetPos;
				extract_rule(state_struct::registry[i]->rule, resultType, commands, targetPos);

				if(commands.size()==0)
				{
					fout<<"\t\t\t\t"<<"//defaultAction"<<endl;
					if(resultType=="object"||resultType=="")
						commands.push_back("standardObject");
					else if(resultType=="value")
						commands.push_back("setProperty");
				}
				for(int j=0;j<commands.size();j++)
				{
					if(commands[j]=="standardObject"||commands[j]=="createObject")
					{
						fout<<"\t\t\t\t"<<"//standardObject"<<endl;
						if(i==0)
							fout<<"\t\t\t\t"<<"QDomDocument curElem = doc;"<<endl;
						else
							fout<<"\t\t\t\t"<<"QDomElement curElem = taskList[curTask].taskElem;"<<endl;
		
						fout<<"\t\t\t\t"<<"//create object."<<endl;
						fout<<"\t\t\t\t"<<"QScriptValue newItemValue = model->getEngine()->newObject();"<<endl;
						fout<<"\t\t\t\t"<<"newItemValue.setProperty(\"*tag*\", curElem.nodeName());"<<endl;
						fout<<endl;
						generateWriteToParentStub(fout);
						generateWriteAttributesStub(fout, i, 4);
						generateWriteChildrenObjectsStub(fout, i, 4);
					}
					else if(commands[j]=="collectTreeAsString")
					{
						fout<<"\t\t\t\t"<<"//collectTreeAsString"<<endl;
						fout<<"\t\t\t\t"<<"QScriptValue newItemValue;"<<endl;
						fout<<"\t\t\t\t"<<"{"<<endl;
						fout<<"\t\t\t\t\t"<<"QString text;" <<endl;
						fout<<"\t\t\t\t\t"<<"QTextStream textStream(&text);"<<endl;
						fout<<"\t\t\t\t\t"<<"taskList[curTask].taskElem.save(textStream, 0);"<<endl;
						fout<<"\t\t\t\t\t"<<"newItemValue = QScriptValue(text);"<<endl;
						fout<<"\t\t\t\t"<<"}"<<endl;
					}
					else if(commands[j]=="collectChildrenTreesAsString"||commands[j]=="collectChildrenTreeAsString") //typo
					{
						fout<<"\t\t\t\t"<<"//collectChildrenTreesAsString"<<endl;
						fout<<"\t\t\t\t"<<"QScriptValue newItemValue;"<<endl;
						fout<<"\t\t\t\t"<<"QString      alltext;"<<endl;
						fout<<"\t\t\t\t"<<"{"<<endl;
						fout<<"\t\t\t\t\t"<<"for(QDomElement childElem = taskList[curTask].taskElem.firstChildElement();"<<endl;
						fout<<"\t\t\t\t\t\t"<<"!childElem.isNull(); childElem = childElem.nextSiblingElement())"<<endl;						
						fout<<"\t\t\t\t\t"<<"{"<<endl;
						fout<<"\t\t\t\t\t\t"<<"QString text;" <<endl;
						fout<<"\t\t\t\t\t\t"<<"QTextStream textStream(&text);"<<endl;
						fout<<"\t\t\t\t\t\t"<<"childElem.save(textStream, 0);"<<endl;
						fout<<"\t\t\t\t\t\t"<<"alltext+=text;"<<endl;
						fout<<"\t\t\t\t\t"<<"}"<<endl;
						fout<<"\t\t\t\t\t"<<"newItemValue = QScriptValue(alltext);"<<endl;
						fout<<"\t\t\t\t"<<"}"<<endl;
					}
					else if(commands[j]=="markAsModel")
					{
						//TODO:
					}
					else if(commands[j]=="skipThis"||commands[j]=="ignoreThis")
					{
						fout<<"\t\t\t\t"<<"//skipThis"<<endl;
						fout<<"\t\t\t\t"<<"QScriptValue newItemValue = taskList[curTask].taskParent;"<<endl;
						fout<<"\t\t\t\t"<<"QDomElement curElem = taskList[curTask].taskElem;"<<endl;
						generateWriteChildrenObjectsStub(fout, i, 4);						
					}
					else if(commands[j]=="createArray")
					{
						fout<<"\t\t\t\t"<<"//createArray"<<endl;
						fout<<"\t\t\t\t"<<"QScriptValue newItemValue;"<<endl;
						fout<<"\t\t\t\t"<<"newItemValue = model->getEngine()->newArray(0);"<<endl;
						fout<<"\t\t\t\t"<<"QDomElement curElem = taskList[curTask].taskElem;"<<endl;
						generateWriteChildrenObjectsStub(fout, i, 4);
					}
					else if(commands[j]=="setProperty")
					{
						fout<<"\t\t\t\t"<<"//setProperty"<<endl;
						fout<<"\t\t\t\t"<<"QScriptValue newItemValue;"<<endl;
						fout<<"\t\t\t\t"<<"newItemValue = QScriptValue(taskList[curTask].taskElem.text());"<<endl;
					}
					else if(commands[j]=="appendToArray")
					{
						if(!targetPos.length()) targetPos = "^";
						if(targetPos[0]=='^')
							fout<<"\t\t\t\t"<<"appendValueToModel(newItemValue, taskList[curTask].taskParent, \""<< targetPos.substr(1)<<"\");"<<endl;
						else if(targetPos[0]=='~')
							fout<<"\t\t\t\t"<<"appendValueToModel(newItemValue, model->getEngine()->globalObject(), \""<< targetPos.substr(1)<<"\");"<<endl;
						
						targetPos = ""; //prevent further processing.
					}
					else if(startWith(commands[j], "getProperty("))
					{
						string propertyName = commands[j].substr(commands[j].find_first_of('(')+1);
						propertyName.erase(propertyName.find_last_of(')'));
						fout<<"\t\t\t\t"<<"//getProperty"<<endl;
						fout<<"\t\t\t\t"<<"QScriptValue newItemValue;"<<endl;
						fout<<"\t\t\t\t"<<"newItemValue = QScriptValue(taskList[curTask].taskElem.attribute(\""<<propertyName<<"\"));"<<endl;

					}
					else if(startWith(commands[j], "collectChildrenAttribute("))
					{
						string propertyName = commands[j].substr(commands[j].find_first_of('(')+1);
						propertyName.erase(propertyName.find_last_of(')'));

						string elemName = propertyName.substr(0, propertyName.find('@'));
						string propName = propertyName.substr(propertyName.find('@')+1);

						fout<<"\t\t\t\t"<<"QList<QScriptValue> arrayItemList;"<<endl;
						fout<<"\t\t\t\t"<<"for(QDomElement childElem = taskList[curTask].taskElem.firstChildElement();"<<endl;
						fout<<"\t\t\t\t\t"<<"!childElem.isNull(); childElem = childElem.nextSiblingElement())"<<endl;
						fout<<"\t\t\t\t"<<"{"<<endl;
						fout<<"\t\t\t\t\t"<<"if(childElem.nodeName()==\""<<elemName<<"\")"<<endl;
						fout<<"\t\t\t\t\t"<<"{"<<endl;
						fout<<"\t\t\t\t\t\t"<<"QString value = childElem.attribute(\""<<propName<<"\");"<<endl;
						fout<<"\t\t\t\t\t\t"<<"if(!value.isNull())"<<endl;
						fout<<"\t\t\t\t\t\t"<<"{"<<endl;
						fout<<"\t\t\t\t\t\t\t"<<"arrayItemList.append(QScriptValue(value));"<<endl;
						fout<<"\t\t\t\t\t\t"<<"}"<<endl;
						fout<<"\t\t\t\t\t"<<"}"<<endl;
						fout<<"\t\t\t\t"<<"}"<<endl;

						fout<<"\t\t\t\t"<<"QScriptValue newItemValue = model->getEngine()->newArray(arrayItemList.count());"<<endl;
						fout<<"\t\t\t\t"<<"for(qint32 i = 0; i < arrayItemList.count(); i++)"<<endl;
						fout<<"\t\t\t\t"<<"newItemValue.setProperty(i, arrayItemList[i]);"<<endl;
					}
					else
					{
						fout<<"\t\t\t\t"<<"//"<<commands[j]<<endl;
					}
				}

				if(targetPos.length())
				{
					if(targetPos[0]=='~')
					{
						fout<<"\t\t\t\t"<<"QScriptValue curTargetItem = model->getEngine()->globalObject();"<<endl;
					}
					else
					{
						fout<<"\t\t\t\t"<<"QScriptValue curTargetItem = taskList[curTask].taskParent;"<<endl;
					}
					fout<<"\t\t\t\t"<<"writeValueToModel("<<"newItemValue"<<", "<<"curTargetItem"<<", \""<<targetPos.substr(1)<<"\");"<<endl;
				}
			}
			fout<< "\t\t\t" << "}" <<endl;
			fout<< "\t\t\t" << "break;" <<endl;
		}
		fout<< "\t\t" << "default"<<":"<<endl;
		fout<< "\t\t\t" << "{" <<endl;

		fout<<"\t\t\t\t"<<"//standardObject"<<endl;
		fout<<"\t\t\t\t"<<"QDomElement curElem = taskList[curTask].taskElem;"<<endl;
		
		fout<<"\t\t\t\t"<<"//create object."<<endl;
		fout<<"\t\t\t\t"<<"QScriptValue newItemValue = model->getEngine()->newObject();"<<endl;
		fout<<"\t\t\t\t"<<"newItemValue.setProperty(\"*tag*\", curElem.nodeName());"<<endl;
		fout<<endl;
		generateWriteToParentStub(fout);
		generateWriteAttributesStub(fout, -1, 4);
		generateWriteChildrenObjectsStub(fout, -1, 4);

		fout<< "\t\t\t" << "}" <<endl;
		fout<< "\t\t\t" << "break;" <<endl;

		fout<< "\t\t" << "};"<<endl;

//		fout<< "contin:" <<endl;
		fout<< "\t\t" << "curTask++;" <<endl;
		fout<< "\t" << "}"<<endl;
		fout<< "\t" << "return true;" << endl;
		fout<< "}" <<endl;
	}


	/*
	for(int i =0;i<lhs_rule.size();i++)
	{
	cerr<<(i+1)<<". "<<lhs_rule[i]<<" => "<< rhs_rule[i]<<endl;
	}*/

	cerr<<"Done."<<endl;
	return 0;
}



int main(int argc, char* argv[])
{
	showlogo();

	if(argc==3&&startWith(argv[2],"-o"))
	{
		return parse(argv[1],argv[2]+2);
	}
	else if(argc==2)
	{
		if(endWith(argv[1], ".parserules"))
		{
			return parse(argv[1],
				(((string)argv[1])
				.substr(0, strlen(argv[1])-strlen(".parserules"))+"Parser")
				.c_str());

		}
		else
		{
			return parse(argv[1],argv[1]);
		}
	}


	usage(argv[0]);
	return 1;
}

