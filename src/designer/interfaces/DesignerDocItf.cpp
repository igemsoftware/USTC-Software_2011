#include "DesignerDocItf.h"

#include "documents/SBML/SBMLDoc.h"
#include "documents/MoDeL/MoDeLDoc.h"
#include "documents/RSBPML/RSBPMLDoc.h"
#include "documents/SBOL/SBOLDoc.h"
#include "documents/FASTA/FASTADoc.h"
#include "documents/EMBL/EMBLDoc.h"
#include "documents/GENBANK/GENBANKDoc.h"
#include "documents/MoDeL_1/MoDeL1Doc.h"

#define LACHESIS_DECLARE_DOCUMENT(className) \
    DesignerDocItf::DocItfRegistry::ItemRegistryInlineAdd docreg_##className (QString( #className ), \
    DesignerDocItf::DocItfRegistryItem(& className ::staticMetaObject))

void DesignerDocItf::initializeIfNotYet()
{
    static bool initialized = false;
    if(!initialized)
    {
        initialized = true;
        LACHESIS_DECLARE_DOCUMENT(SBMLDoc);
        LACHESIS_DECLARE_DOCUMENT(MoDeLDoc);
        LACHESIS_DECLARE_DOCUMENT(RSBPMLDoc);
        LACHESIS_DECLARE_DOCUMENT(SBOLDoc);
        LACHESIS_DECLARE_DOCUMENT(FASTADoc);
        LACHESIS_DECLARE_DOCUMENT(EMBLDoc);
        LACHESIS_DECLARE_DOCUMENT(GENBANKDoc);
        LACHESIS_DECLARE_DOCUMENT(MoDeL1Doc);
    }
}

DesignerDocItf::DesignerDocItf() :
    QObject(NULL) ,
    currentModel(NULL),
    modified(false)
{

}

bool DesignerDocItf::saveToFile()
{
    return true;
}


const QMetaObject* DesignerDocItf::getBestFitDocumentTypeForFile(QString pathName)
{
    const size_t arraySize = DocItfRegistry::count();
    struct fitStatusStucture
    {
        extentValue extent;
        const QMetaObject* metaObject;
    } retValues[arraySize];
    size_t bestFit = arraySize;
    for(size_t i=0;i<arraySize;i++)
    {
        DesignerDocItf* newDocument = (DesignerDocItf*)DocItfRegistry::item(i).metaObject->newInstance();
        QFile file(pathName);
        retValues[i].extent = newDocument->checkIfFileFitsDocumentType(file);

        retValues[i].metaObject = DocItfRegistry::item(i).metaObject;

        if((retValues[i].extent!=NOTACCEPTABLE) &&
                ( bestFit==arraySize ||
                  fitIsBetterThan(retValues[i].extent, retValues[bestFit].extent)))
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

DesignerDocItf* DesignerDocItf::createEmptyDoc(QString docName)
{
    DocItfRegistryItem metaObj = DocItfRegistry::find(docName);
    if(metaObj.metaObject)
        return dynamic_cast<DesignerDocItf*>
                (metaObj.metaObject->newInstance());

    return NULL;
}

DesignerModelItf * DesignerDocItf::getCurrentModel(QString modelName)
{
    if(currentModel)
        return currentModel;
    return DesignerModelItf::createModel(modelName, this);
}

