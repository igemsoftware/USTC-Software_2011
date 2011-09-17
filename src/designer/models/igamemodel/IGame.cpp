#include "IGame.h"

IGameModel::IGameModel(DesignerDocComponent *newDoc) :
    DesignerModelComponent(newDoc)
{
}

QStringList IGameModel::getSupportedViewList() const
{
    QStringList supportedViewList;
    supportedViewList.append("AssemblyView");

    return supportedViewList;
}

QStringList IGameModel::getSupportedDocumentList() const
{
    QStringList supportedDocumentList;
    supportedDocumentList.append("MoDeL");
    return supportedDocumentList;
}
