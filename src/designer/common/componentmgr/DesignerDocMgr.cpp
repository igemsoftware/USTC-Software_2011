#include "DesignerDocMgr.h"


#include "documents/SBML/SBMLDoc.h"
#include "documents/MoDeL/MoDeLDoc.h"
#include "documents/RSBPML/RSBPMLDoc.h"
#include "documents/SBOL/SBOLDoc.h"
#include "documents/FASTA/FASTADoc.h"
#include "documents/EMBL/EMBLDoc.h"
#include "documents/GENBANK/GENBANKDoc.h"
#include "documents/MoDeL_1/MoDeL1Doc.h"
#include "documents/USML/USMLDoc.h"

#define LACHESIS_DECLARE_DOCUMENT(className, supportSave, titleText, filterText) \
    DesignerDocMgr::DocItfRegistry::ItemRegistryInlineAdd docreg_##className (QString( #className ), \
    DesignerDocMgr::DocItfRegistryItem(& className ::staticMetaObject, supportSave, titleText, filterText))

void DesignerDocMgr::initializeIfNotYet()
{
    static bool initialized = false;
    if(!initialized)
    {
        initialized = true;
        LACHESIS_DECLARE_DOCUMENT(SBMLDoc,      false, "SBML File",     "*.xml *.sbml");
        LACHESIS_DECLARE_DOCUMENT(MoDeLDoc,     false, "MoDeL File",    "*.model");
        LACHESIS_DECLARE_DOCUMENT(RSBPMLDoc,    false, "RSBPML File",   "*.xml *.rsbpml");
        LACHESIS_DECLARE_DOCUMENT(SBOLDoc,      false, "SBOL File",     "*.xml");
        LACHESIS_DECLARE_DOCUMENT(FASTADoc,     true, "FASTA File",    "*.xml *.fasta");
        LACHESIS_DECLARE_DOCUMENT(EMBLDoc,      true, "EMBL File",     "*.xml *.embl");
        LACHESIS_DECLARE_DOCUMENT(GENBANKDoc,   true, "GenBank File",  "*.xml *.genbank");
        LACHESIS_DECLARE_DOCUMENT(MoDeL1Doc,    false, "MoDeL-1 File",  "*.xml");
        LACHESIS_DECLARE_DOCUMENT(USMLDoc,      true , "USML File",     "*.xml *.usml");
    }
}
