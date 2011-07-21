#include "DesignerDocItf.h"

#include "documents/SBML/SBMLDoc.h"
#include "documents/MoDeL/MoDeLDoc.h"
#include "documents/RSBPML/RSBPMLDoc.h"

static QMetaObject metaObjectsOfDocuments[] = {
    SBMLDoc::staticMetaObject,
    MoDeLDoc::staticMetaObject,
    RSBPMLDoc::staticMetaObject
};

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


QMetaObject* DesignerDocItf::getBestFitDocumentTypeForFile(QString pathName)
{
    const size_t arraySize = sizeof(metaObjectsOfDocuments)/sizeof(metaObjectsOfDocuments[0]);
    struct fitStatusStucture
    {
        extentValue extent;
        QMetaObject* metaObject;
    } retValues[arraySize];
    size_t bestFit = arraySize;
    for(size_t i=0;i<arraySize;i++)
    {
        DesignerDocItf* newDocument = (DesignerDocItf*)metaObjectsOfDocuments[i].newInstance();
        QFile file(pathName);
        retValues[i].extent = newDocument->checkIfFileFitsDocumentType(file);

        retValues[i].metaObject = &metaObjectsOfDocuments[i];

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
    const size_t arraySize = sizeof(metaObjectsOfDocuments)/sizeof(metaObjectsOfDocuments[0]);
    for(size_t i=0;i<arraySize;i++)
    {
        if(docName==metaObjectsOfDocuments[i].className())
        {
            return (DesignerDocItf*)metaObjectsOfDocuments[i].newInstance();
        }
    }
    return NULL;
}

DesignerModelItf * DesignerDocItf::getCurrentModel(QString modelName)
{
    if(currentModel)
        return currentModel;
    return DesignerModelItf::createModel(modelName, this);
}

