#include "DesignerXMLDocParser.h"

DesignerXMLDocParser::DesignerXMLDocParser()   
{
}

void DesignerXMLDocParser::appendValueToModel(QScriptValue value, QScriptValue root, QString path)
{
    QStringList pathList = path.split('/', QString::SkipEmptyParts);
    QScriptValue item = root;
    if(pathList.count()==0)
    {
        if(!item.isArray())
            Q_ASSERT_X(false, "XMLDocParser::writeValueToModel", "This operation is not permitted!");
    }
    else
    {
        for(int i=0;i<pathList.count();i++)
        {
            QScriptValue newItem = item.property(pathList[i]);
            if(i!=pathList.count()-1)
            {
                if(!newItem.isObject())
                {
                    newItem = root.engine()->newObject();
                    item.setProperty(pathList[i], newItem);
                }
            }
            else
            {
                if(!newItem.isArray())
                {
                    newItem = root.engine()->newArray(0);
                    item.setProperty(pathList[i], newItem);
                }
            }
            item = newItem;
        }
    }

    int arrayLength = item.property("length").toInt32();
    item.setProperty(arrayLength, value);
    item.setProperty("length", QScriptValue(arrayLength+1));
}

void DesignerXMLDocParser::writeValueToModel(QScriptValue value, QScriptValue root, QString path)
{
    QStringList pathList = path.split('/', QString::SkipEmptyParts);
    QScriptValue item = root;
    if(pathList.count()==0)
        Q_ASSERT_X(false, "XMLDocParser::writeValueToModel", "This operation is not permitted!");
    else
    {
        for(int i=0;i<pathList.count()-1;i++)
        {
            QScriptValue newItem = item.property(pathList[i]);
            if(!newItem.isObject())
            {
                newItem = root.engine()->newObject();
                item.setProperty(pathList[i], newItem);
            }
            item = newItem;
        }
    }
    item.setProperty(pathList[pathList.count()-1], value);
}
