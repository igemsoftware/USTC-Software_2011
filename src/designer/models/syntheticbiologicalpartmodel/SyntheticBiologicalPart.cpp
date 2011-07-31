#include "SyntheticBiologicalPart.h"

SyntheticBiologicalPartModel::SyntheticBiologicalPartModel(DesignerDocItf *newDoc) :
    DesignerModelItf(newDoc)
{

}

QStringList SyntheticBiologicalPartModel::getSupportedViewList() const
{
    QStringList supportedViewList;
    supportedViewList.append("PartView");

    return supportedViewList;
}

QStringList SyntheticBiologicalPartModel::getSupportedDocumentList() const
{
    QStringList supportedDocumentList;
    supportedDocumentList.append("USMLDoc");
    supportedDocumentList.append("SBOLDoc");
    supportedDocumentList.append("FASTADoc");
    supportedDocumentList.append("RSBPMLDoc");
    supportedDocumentList.append("EMBLDoc");
    supportedDocumentList.append("GENBANKDoc");
    return supportedDocumentList;
}


