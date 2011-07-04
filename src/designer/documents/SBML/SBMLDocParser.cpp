#include <QtXml>
#include "models/reactionnetworkmodel/ReactionNetwork.h"
#include "SBMLDocParser.h"

SBMLDocParser::SBMLDocParser()
{
}

bool SBMLDocParser::parse(DesignerModelItf& modelItf, QDomElement& docElem)
{
    ReactionNetworkModel& model = dynamic_cast<ReactionNetworkModel&>(modelItf);
    DesignerModelFormatProxyItf* importProxy = model.createImportProxy("ReactionNetworkSBMLImportProxy");

    if(!importProxy) return false;

    for(int attrIndex = 0 ; attrIndex < docElem.attributes().count(); attrIndex++)
    {
        importProxy->setModelObjectProperty(0,
                                     docElem.attributes().item(attrIndex).nodeName(),
                                     docElem.attributes().item(attrIndex).nodeValue());
    }

    for(QDomElement SBMLModelElem = docElem.firstChildElement();
        !SBMLModelElem.isNull(); SBMLModelElem = SBMLModelElem.nextSiblingElement())
    {
        DesignerModelItf::modelObjectIndex index = importProxy->createModelObject(0, &SBMLModelElem);

    }
    return true;
}
