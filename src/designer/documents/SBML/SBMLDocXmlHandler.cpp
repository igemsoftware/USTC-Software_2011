#include "SBMLDocXmlHandler.h"

SBMLDocXmlHandler::SBMLDocXmlHandler()
{
}


bool SBMLDocXmlHandler::startDocument()
{
    printf("startDocument\n");
    return TRUE;
}

bool SBMLDocXmlHandler::startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts)
{
    printf("startElement: ns=%s, ln=%s, qname=%s\n", (char*)namespaceURI.toAscii().data(), (char*)localName.toAscii().data(), (char*)qName.toAscii().data());
/*
    static bool eatComma;
    if(qName=="listOfCompartments")
    {
        printf("Compartments:\n");
    }
    else if(qName=="compartment")
    {
        if(atts.index("id")!=-1)
        {
            printf(atts.value("id").toAscii());
            printf("\n");
        }
    }
    else if(qName=="listOfSpecies")
    {
        printf("Species:\n");
    }
    else if(qName=="species")
    {
        if(atts.index("id")!=-1)
        {
            printf(atts.value("id").toAscii());
            printf("\n");
        }
    }
    else if(qName=="listOfParameters")
    {
        printf("Parameters:\n");
    }
    else if(qName=="parameter")
    {
        if(atts.index("id")!=-1)
        {
            printf(atts.value("id").toAscii());
            printf("=");
            printf(atts.value("value").toAscii());
            printf("\n");
        }
    }
    else if(qName=="listOfReactions")
    {
        printf("Reactions:\n");
    }
    else if(qName=="reaction")
    {
        if(atts.index("id")!=-1)
        {
            printf(atts.value("id").toAscii());
            printf(": ");
        }
    }
    else if(qName=="listOfReactants")
    {
        eatComma = true;
    }
    else if(qName=="listOfProducts")
    {
        eatComma = true;
        printf("->");
    }
    else if(qName=="speciesReference")
    {
        if(!eatComma)
        {
            printf("+");
        }
        eatComma = false;
        if(atts.index("species")!=-1)
        {
            QString stoichiometry = atts.value("stoichiometry");
            if(stoichiometry!="1"&&stoichiometry!="")
            {
                printf(stoichiometry.toAscii());
            }
            printf(atts.value("species").toAscii());
        }
    }
    else
    {
//        printf( "%s%s\n", (const char*)indent.toAscii(), (const char*)qName.toAscii() );
//        indent += "    ";
    }*/
    return TRUE;

}

bool SBMLDocXmlHandler::endElement(const QString& namespaceURI, const QString& localName, const QString& qName)
{
    printf("startElement: ns=%s, ln=%s, qname=%s\n", (char*)namespaceURI.toAscii().data(), (char*)localName.toAscii().data(), (char*)qName.toAscii().data());
/*
    if(qName=="listOfCompartments")
    {
        printf("\n");
    }
    else if(qName=="listOfSpecies")
    {
        printf("\n");
    }
    else if(qName=="listOfParameters")
    {
        printf("\n");
    }
    else if(qName=="listOfReactions")
    {
        printf("\n");
    }
    else if(qName=="reaction")
    {
        printf("\n");
    }
*/
    return TRUE;
}
