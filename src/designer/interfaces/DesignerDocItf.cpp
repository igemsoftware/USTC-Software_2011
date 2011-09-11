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

DesignerDocComponent::DesignerDocComponent() :
    QObject(NULL) ,
    currentModel(NULL)
{

}


bool DesignerDocComponent::loadFromDiskFile(QString fileName)
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
        getCurrentModel()->requestUpdate(DesignerModelComponent::updateByStorage);
    }

    return retValue;
}

bool DesignerDocComponent::saveToDiskFile(QString fileName)
{
    QFile file(fileName);
    if(file.exists()&&!file.remove()) return false;
    bool retValue = saveToFile(file);

    if(retValue)
    {
        this->documentFileInfo = QFileInfo(file);
        this->readOnly = false;
        getCurrentModel()->setModified(false);
        getCurrentModel()->requestUpdate(DesignerModelComponent::updateByStorage);
    }

    return retValue;
}

bool DesignerDocComponent::updateFile()
{
    return saveToDiskFile(documentFileInfo.absoluteFilePath());
}

DesignerModelComponent * DesignerDocComponent::getCurrentModel(QString modelName)
{
    if(currentModel)
        return currentModel;
    return DesignerModelMgr::createModel(modelName, this);
}

