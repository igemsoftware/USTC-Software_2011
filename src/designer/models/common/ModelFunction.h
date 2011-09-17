#ifndef MODELFUNCTION_H
#define MODELFUNCTION_H

#include <QList>
#include <QDomDocument>
/*
QScriptValue createMathObjectFromContentMathML(QDomElement& rootElem)
{
    QList<QString> resultList;

    QString leftBracket = "[", rightBracket = "]";

    QList<QDomElement> workStack;

    workStack.push_back(rootElem.firstChildElement());

//    resultList.push_back(leftBracket);
    while(workStack.count())
    {
        QDomElement elem = workStack.last();

        if(!elem.isNull())
        {
            QDomElement childElem = elem.firstChildElement();
            if(elem.attributes().count()||!childElem.isNull())
            {
                resultList.push_back(leftBracket);
                if(elem.attributes().count())
                {
                    resultList.push_back(leftBracket);
                    resultList.push_back(elem.nodeName());
                    for(i = 0; i < elem.attributes().count(); i++)
                    {
                        resultList.push_back(elem.attributes().item(i).nodeName());
                        resultList.push_back(elem.attributes().item(i).nodeValue());
                    }
                    resultList.push_back(rightBracket);
                }
                else
                {
                    resultList.push_back(elem.nodeName());
                }



                resultList.push_back(rightBracket);

            }

        }

        while(!elem.isNull())
        {

            elem.attributes().count();
            childElem.text();
            if(childElem.isNull())
            elem.nodeName();

            elem=elem.nextSiblingElement();
        }
        resultList.push_back(rightBracket);
        workStack.pop_back(elem);
    }
}
*/
#endif // MODELFUNCTION_H
