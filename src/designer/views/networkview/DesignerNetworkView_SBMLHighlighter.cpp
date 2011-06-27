#include "DesignerNetworkView_SBMLHighlighter.h"

NetworkView_SBMLHighlighter::NetworkView_SBMLHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{

}


void NetworkView_SBMLHighlighter::highlightBlock ( const QString & text )
{
    QString generalXMLPattern = "<[^<]+>";
    QRegExp generalXMLRegex(generalXMLPattern);
    int index = text.indexOf(generalXMLRegex);
    while (index>= 0) {
        int length = generalXMLRegex.matchedLength();
        setFormat(index, length, getSyntaxFormat(text.mid(index+1, length-2)));
        index = text.indexOf(generalXMLRegex, index + length);
    }

}

QTextCharFormat NetworkView_SBMLHighlighter::getSyntaxFormat (const QString & text)
{
    static struct syntax_rule
    {
        QString         rule_pattern;
        QTextCharFormat rule_format;
    } rules[16];
    static size_t  rulecount = 0;
    if(!rulecount)
    {
        rules[rulecount].rule_pattern =
                "^\\?xml(\\W|$)";
        rules[rulecount].rule_format.setFontWeight(QFont::Bold);
        rules[rulecount].rule_format.setForeground(Qt::darkGreen);
        rulecount++;

        rules[rulecount].rule_pattern =
                "^/?("
                "sbml|model|listOfUnitDefinitions|unitDefinition|listOfUnits|unit"
                "|listOfCompartments|compartment|listOfSpecies|species|listOfParameters|parameter|listOfRules|assignmentRule"
                "|listOfReactions|reaction|listOfReactants|kineticLaw|listOfProducts|listOfModifiers|speciesReference|modifierSpeciesReference"
                ")(\\W|$)";
        rules[rulecount].rule_format.setFontWeight(QFont::Bold);
        rules[rulecount].rule_format.setForeground(Qt::blue);
        rulecount++;

        //math
        rules[rulecount].rule_pattern =
                "^/?("
                "math|ci|apply|plus/|times/|power/|divide/"
                ")(\\W|$)";
        rules[rulecount].rule_format.setFontWeight(QFont::Bold);
        rules[rulecount].rule_format.setForeground(Qt::darkMagenta);
        rulecount++;

        //notes
        rules[rulecount].rule_pattern =
                "^/?("
                "notes|body|a|p|br"
                ")(\\W|$)";
        rules[rulecount].rule_format.setFontWeight(QFont::Bold);
        rules[rulecount].rule_format.setForeground(Qt::gray);
        rulecount++;

        //annotations
        rules[rulecount].rule_pattern =
                "^/?(annotation|[A-Za-z]*:[A-Za-z]*)(\\W|$)";
        rules[rulecount].rule_format.setFontWeight(QFont::Bold);
        rules[rulecount].rule_format.setForeground(Qt::magenta);
        rulecount++;

        rules[rulecount].rule_pattern=".*";
        rules[rulecount].rule_format.setFontWeight(QFont::Bold);
        rules[rulecount].rule_format.setForeground(Qt::darkGray);
        rulecount++;
    }

    for(size_t i=0; i<rulecount; i++)
    {
        QRegExp regex(rules[i].rule_pattern);
        if(text.indexOf(regex)>=0)
        {
            return rules[i].rule_format;
        }
    }
    return rules[rulecount-1].rule_format;
}
