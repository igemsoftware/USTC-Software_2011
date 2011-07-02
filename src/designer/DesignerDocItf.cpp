#include "DesignerDocItf.h"

#include "Documents/SBML/SBMLDoc.h"

static QMetaObject metaObjectsOfDocuments[] = {
    SBMLDoc::staticMetaObject,

};


QMetaObject* DesignerDocItf::getFileFitsDocumentTypesStatus(QString pathName)
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


DesignerDocItf::DesignerDocItf(QObject *parent) :
    QObject(parent)
{

}
