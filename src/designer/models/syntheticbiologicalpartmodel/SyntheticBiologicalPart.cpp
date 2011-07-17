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
