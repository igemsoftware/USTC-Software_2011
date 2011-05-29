#include <sbml/SBMLTypes.h>
#include <QtScript>
#include <iostream>

#include "common/utils/utils.h"

using namespace std;
using namespace lachesis::common::utils;

namespace lachesis
{

namespace designer
{

namespace core
{

namespace bionetwork_sbml
{


void import_bionetwork_sbml_file(char* filename)
{
	//load file
	SBMLDocument* doc = readSBML(filename);
	//do check
	if(document->getNumErrors()!=0)
	{
		cerr << getprogname() << ": " << document->getNumErrors() << " error(s) occurred loading file " << filename << "." <<endl;
		
	}
	
}


}
}
}
}