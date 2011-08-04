#include "DesignerDocItf.h"

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
    DesignerDocItf::DocItfRegistry::ItemRegistryInlineAdd docreg_##className (QString( #className ), \
    DesignerDocItf::DocItfRegistryItem(& className ::staticMetaObject, supportSave, titleText, filterText))

void DesignerDocItf::initializeIfNotYet()
{
    static bool initialized = false;
    if(!initialized)
    {
        initialized = true;
        LACHESIS_DECLARE_DOCUMENT(SBMLDoc,      false, "SBML File",     "*.xml *.sbml");
        LACHESIS_DECLARE_DOCUMENT(MoDeLDoc,     false, "MoDeL File",    "*.xml *.model");
        LACHESIS_DECLARE_DOCUMENT(RSBPMLDoc,    false, "RSBPML File",   "*.xml *.rsbpml");
        LACHESIS_DECLARE_DOCUMENT(SBOLDoc,      false, "SBOL File",     "*.xml");
        LACHESIS_DECLARE_DOCUMENT(FASTADoc,     true, "FASTA File",    "*.xml *.fasta");
        LACHESIS_DECLARE_DOCUMENT(EMBLDoc,      false, "EMBL File",     "*.xml *.embl");
        LACHESIS_DECLARE_DOCUMENT(GENBANKDoc,   false, "GenBank File",  "*.xml *.genbank");
        LACHESIS_DECLARE_DOCUMENT(MoDeL1Doc,    false, "MoDeL-1 File",  "*.xml");
        LACHESIS_DECLARE_DOCUMENT(USMLDoc,      true , "USML File",     "*.xml *.usml");
    }
}

DesignerDocItf::DesignerDocItf() :
    QObject(NULL) ,
    currentModel(NULL)
{

}


bool DesignerDocItf::loadFromDiskFile(QString fileName)
{
    QFile file(fileName);
    bool isReadOnly = false;
    if(!file.open(QFile::ReadWrite))
    {
        isReadOnly = true;
        if(!file.open(QFile::ReadOnly))
            return false;
    }
    file.close();

    bool retValue = loadFromFile(file);
    if(retValue)
    {
        this->documentFileInfo = QFileInfo(file);
        this->readOnly = isReadOnly;
        getCurrentModel()->setModified(false);
        getCurrentModel()->requestUpdate(DesignerModelItf::updateByStorage);
    }

    return retValue;
}

bool DesignerDocItf::saveToDiskFile(QString fileName)
{
    QFile file(fileName);
    if(file.exists()&&!file.remove()) return false;
    bool retValue = saveToFile(file);

    if(retValue)
    {
        this->documentFileInfo = QFileInfo(file);
        this->readOnly = false;
        getCurrentModel()->setModified(false);
        getCurrentModel()->requestUpdate(DesignerModelItf::updateByStorage);
    }

    return retValue;
}

bool DesignerDocItf::updateFile()
{
    return saveToDiskFile(documentFileInfo.absoluteFilePath());
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

DesignerDocItf* DesignerDocItf::createEmptyDoc(QString docName, DesignerModelItf* model)
{
    DocItfRegistryItem metaObj = DocItfRegistry::find(docName);
    if(metaObj.metaObject)
    {
        DesignerDocItf* newDoc = dynamic_cast<DesignerDocItf*>
                (metaObj.metaObject->newInstance());
        if(newDoc)
            newDoc->currentModel=model;
        return newDoc;
    }

    return NULL;
}

bool DesignerDocItf::isDocTypeSaveSupported(QString docName)
{
    DocItfRegistryItem metaObj = DocItfRegistry::find(docName);
    if(metaObj.metaObject)
        return metaObj.supportSave;

    return false;
}

QString DesignerDocItf::getDocTypeTitle(QString docName)
{
    DocItfRegistryItem metaObj = DocItfRegistry::find(docName);
    if(metaObj.metaObject)
        return metaObj.titleText;

    return QString();
}

QString DesignerDocItf::getDocTypeFilter(QString docName)
{
    DocItfRegistryItem metaObj = DocItfRegistry::find(docName);
    if(metaObj.metaObject)
        return tr("%1 (%2)").arg(metaObj.titleText, metaObj.filterText);

    return QString();
}

QStringList DesignerDocItf::getDocTypeList()
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

DesignerModelItf * DesignerDocItf::getCurrentModel(QString modelName)
{
    if(currentModel)
        return currentModel;
    return DesignerModelItf::createModel(modelName, this);
}

