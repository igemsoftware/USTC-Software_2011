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


const QMetaObject* DesignerDocMgr::getBestFitDocumentTypeForFile(QString pathName)
{
    const size_t arraySize = DocItfRegistry::count();
    struct fitStatusStucture
    {
        DesignerDocComponent::extentValue extent;
        const QMetaObject* metaObject;
    } retValues[arraySize];
    size_t bestFit = arraySize;
    for(size_t i=0;i<arraySize;i++)
    {
        DesignerDocComponent* newDocument = (DesignerDocComponent*)DocItfRegistry::item(i).metaObject->newInstance();
        QFile file(pathName);
        retValues[i].extent = newDocument->checkIfFileFitsDocumentType(file);

        retValues[i].metaObject = DocItfRegistry::item(i).metaObject;

        if((retValues[i].extent!=DesignerDocItf::NOTACCEPTABLE) &&
                ( bestFit==arraySize ||
                  DesignerDocComponent::fitIsBetterThan(retValues[i].extent, retValues[bestFit].extent)))
        {
            bestFit = i;
        }
    }
    if(bestFit==arraySize)
    {
        return NULL;
    }
    return retValues[bestFit].metaObject;
}

DesignerDocComponent* DesignerDocMgr::createEmptyDoc(QString docName, DesignerModelComponent* model)
{
    DocItfRegistryItem metaObj = DocItfRegistry::find(docName);
    if(metaObj.metaObject)
    {
        DesignerDocComponent* newDoc = dynamic_cast<DesignerDocComponent*>
                (metaObj.metaObject->newInstance());
        if(newDoc)
            newDoc->currentModel=model;
        return newDoc;
    }

    return NULL;
}

bool DesignerDocMgr::isDocTypeSaveSupported(QString docName)
{
    DocItfRegistryItem metaObj = DocItfRegistry::find(docName);
    if(metaObj.metaObject)
        return metaObj.supportSave;

    return false;
}

QString DesignerDocMgr::getDocTypeTitle(QString docName)
{
    DocItfRegistryItem metaObj = DocItfRegistry::find(docName);
    if(metaObj.metaObject)
        return metaObj.titleText;

    return QString();
}

QString DesignerDocMgr::getDocTypeFilter(QString docName)
{
    DocItfRegistryItem metaObj = DocItfRegistry::find(docName);
    if(metaObj.metaObject)
        return QObject::tr("%1 (%2)").arg(metaObj.titleText, metaObj.filterText);

    return QString();
}

QStringList DesignerDocMgr::getDocTypeList()
{
    QStringList docTypeList;
    for(int i = 0; i < DocItfRegistry::count(); i++)
    {
        if(DocItfRegistry::item(i).metaObject)
        {
            docTypeList<<DocItfRegistry::item(i).metaObject->className();
        }
    }
    return docTypeList;
}
