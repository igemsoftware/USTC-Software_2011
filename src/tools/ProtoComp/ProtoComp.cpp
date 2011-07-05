#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <sstream>
using namespace std;

void showlogo()
{
  cerr<<"Biology data structure description compiler v1"<<endl;
  cerr<<"by CrLF0710"<<endl;
  cerr<<"----------------------------------"<<endl;
}

void usage (char* cmdName)
{
  cerr<<"Usage: " <<cmdName <<" <input-file> -o<output-file>"<<endl;
  cerr<<endl;
}

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

string result_type_name_to_cpp(string model_type)
{
    if(model_type=="symbol"||model_type=="predicate"||
       model_type=="mathexpr"||model_type=="mathsegexpr"||
       model_type=="symbollist"||model_type=="valuelist"||
       model_type=="precisevalue")
        return model_type+"_t";
    return model_type;
}

string namespaceName;
vector<string> classList;


void parse_definitions(istream& _input, ostream& _output)
{
  string line;
  getline(_input, line);
  char buffer[256];
  strcpy(buffer, line.c_str());
  char* pchar = buffer;
  
  while(isspace(*pchar)) pchar++;
  if(*pchar=='\0')
  {
    _output<<endl;
    return;
  }
  else if(*pchar=='\x7F') //generate an error.
  {
    throw(5);
  }
  else if(*pchar=='#') //comment
  {
    _output<<"\t// "<<*(pchar+1)<<endl;
    return;
  }
  else if(*pchar=='%') //type
  {
    string typeName,typeDest,typeEdit;
    while((_input>>typeName)&&(typeName!="end"))
    {
      _output<<"\tusing lachesis::" <<typeName<<"_t;"<<endl;
    }
    getline(_input, typeName);
    return;
  }
  else  //class
  {
    char* colonpos = strchr(pchar, ':');
    string classname;
    if(colonpos)
    {
      *colonpos='\0';
      _output<<"\tstruct "<<pchar<<endl;
      classname=pchar;
      classList.push_back(classname);
      
      _output<<"\t{"<<endl;
      pchar = colonpos+1;

      string fields[16][5];
      int curindex = 0;
      int curfield = 0;
      
      while((_input>>fields[curindex][0])&&(fields[curindex][0]!="end"))
      {
        if(fields[curindex][0]=="#")
        {
          getline(_input, line);
          
          continue;            
        }
        
        curfield = 1;
        while(_input>>fields[curindex][curfield]&&
              fields[curindex][curfield]!=";")
        {
          if(endWith(fields[curindex][curfield],";"))
          {
            _input.putback(';');
            fields[curindex][curfield] =
              fields[curindex][curfield].substr(0,
                     fields[curindex][curfield].length()-1);
            
          }
          curfield++;
        }
        
        curindex++;        
      }
	
	
      for(int i=0;i<curindex;i++)
      {
        _output<<"\t\t";
        
        if(fields[i][2]=="instance")
        {
          _output<<"// ";
        }
        
        _output<<result_type_name_to_cpp(fields[i][0])<<" ";
        _output<<fields[i][1]<<";";
        
        if(fields[i][2]=="instance")
        {
          _output<<" ;; instance-value";
        }
        _output<<endl;
      }

      _output<<endl;
      _output<<"\t\tstatic QScriptValue toScriptValue(QScriptEngine *engine, "
             <<"  const "<<classname<<" &s)"<<endl;

      _output<<"\t\t{"<<endl;
      _output<<"\t\t\tQScriptValue obj = engine->newObject();"<<endl;

      for(int i=0;i<curindex;i++)
      {
        if(fields[i][2]!="instance")
        {
          _output<<"\t\t\tobj.setProperty(\""<<fields[i][1]<<"\", ";
          _output<<"convertModelTypeToScriptValue(engine, s."<<fields[i][1]<<"))";
          _output<<";"<<endl;
        }
      }      
      
      _output<<"\t\t\treturn obj;"<<endl;
      _output<<"\t\t}"<<endl;

      _output<<endl;

      _output<<"\t\tstatic void fromScriptValue(const QScriptValue &obj, "
             <<classname<<" &s)"<<endl;
      _output<<"\t\t{"<<endl;
      
      for(int i=0;i<curindex;i++)
      {
        if(fields[i][2]!="instance")
        {
          _output<<"\t\t\ts."<<fields[i][1]<<" = ";
          _output<<"qscriptvalue_cast<"<<result_type_name_to_cpp(fields[i][0])<<">(";
          _output<<"obj.property(\""<<fields[i][1]<<"\")";
          _output<<");"<<endl;
        }
      }  
      _output<<"\t\t}"<<endl;

      _output<<"\t\t/*"<<endl;

      _output<<"\t\tinline static const QList<PropertyDescriptor> listProperty()"<<endl;
      _output<<"\t\t{"<<endl;
      _output<<"\t\t\tQList<PropertyDescriptor> propertyList;"<<endl;
      for( int i = 0 ; i < curindex ; i++ )
	  {
		_output<<"\t\t\tpropertyList.push_back( PropertyDescriptor( \""<<fields[i][1]<<"\" , QVariant::"<<((fields[i][0]=="bool")?"Bool":fields[i][0])<<" ) );"<<endl;
	  }
      _output<<"\t\t\treturn propertyList;"<<endl;
      _output<<"\t\t}"<<endl;

      _output<<"\t\t*/"<<endl;

      _output<<"\t};"<<endl;
      
	  
	  
//      _output<<"\tQ_DECLARE_METATYPE("<<classname<<");"<<endl;
      
    }
    else
    {
      _output<<"// Error: colon not found!!!!";
      _input.putback('\x7F'); //to generate an error.
      return;
    }
  }
}


int parse(const char* _inputfile, const char* _outputfile)
{
  string inputfile = _inputfile;
  string outputfile = _outputfile;
  if(!endWith(_outputfile, ".h"))
    outputfile+=".h";
  
    
  ifstream fin(inputfile.c_str());
  ofstream fout(outputfile.c_str());
  
  string line;
  if(!fin||!fout)
  {
    cerr<<"Can't open file"<<endl;   return 1;
  }

  //signature
  getline(fin,line);
  if(line!="[DESCRIPTION]")
  {
    cerr<<"Input file format incorrect."<<endl;return 1;    
  }

  //write header
  {
    fout<<"// THIS FILE IS AUTO-GENERATED BY PROTOCOMP."<<endl;
    fout<<"// PLEASE DON'T EDIT THIS FILE MANUALLY."<<endl;
    fout<<"// Generate Time: "<<result_current_time()<<endl;
    fout<<"#ifndef "<<result_include_once_macro_name(outputfile)<<endl;
    fout<<"#define "<<result_include_once_macro_name(outputfile)<<endl;
    fout<<endl;
    fout<<"#include <QMetaType>"<<endl;
    fout<<"#include <QScriptValue>"<<endl;
    fout<<"#include <QVariant>"<<endl;
    fout<<endl;
    fout<<"#include \"models/common/ModelSymbol.h\""<<endl;
    fout<<endl;
    fout<<"";
  }

  namespaceName = result_split_path(inputfile, 2);

  //namespace start
  {
    fout<<"namespace "<<namespaceName<<endl;
    fout<<"{"<<endl;
  }
  

  while(!fin.eof())
  {
    ostringstream oss;
    
    try
    {
      parse_definitions(fin,oss);

      fout<<oss.str()<<endl;
      
    }
    catch(...)
    {
      fout<<endl;      
      fout<<"// **************************************************"<<endl;
      fout<<"//   There was an error in the prototype file."<<endl;
      fout<<"//   So we lost the lines here."<<endl;
      fout<<"// **************************************************"<<endl;
      fout<<endl;
    }
  }  
  
  //namespace end
  {
    fout<<"}"<<endl;
  }

  //declare METATYPES;

  for(size_t i = 0; i< classList.size();i++)
    fout<<"\tQ_DECLARE_METATYPE("<<namespaceName<<"::"<<classList[i]<<");"<<endl;

  //footer
  {
    fout<<endl;
    fout<<"#endif // "<<result_include_once_macro_name(outputfile)<<endl;
  }
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
    if(endWith(argv[1], ".prototype"))
    {
      return parse(argv[1],
              ((string)argv[1])
            .substr(0, strlen(argv[1])-strlen(".prototype"))
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




