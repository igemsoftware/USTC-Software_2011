#include <QtScript>
#include "DesignerPropertiesPanelWidget.h"

DesignerPropertiesPanelWidget::DesignerPropertiesPanelWidget(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    invalidWidget = new QLabel(this);
    invalidWidget->setAlignment(Qt::AlignCenter);
    invalidWidget->setText(tr("Not Available"));
    gridLayout->addWidget(invalidWidget, 0, 0, 1, 1);

    propertiesWidget = new QTreeWidget(this);
    gridLayout->addWidget(propertiesWidget, 0, 0, 1, 1);

    QStringList propertiesHeaderLabels;
    propertiesHeaderLabels<<tr("Property")<<tr("Value");
    propertiesWidget->setHeaderLabels( propertiesHeaderLabels );
    propertiesWidget->setWordWrap(true);

//    propertiesWidget->clear();
    updateTarget(QScriptValue(QScriptValue::UndefinedValue));
}

DesignerPropertiesPanelWidget::ScriptValueType DesignerPropertiesPanelWidget::getScriptValueType(const QScriptValue& value)
{
    if(value.isUndefined()) return Undefined;
    else if(value.isNull()) return Null;
    else if(value.isBoolean()) return Boolean;
    else if(value.isNumber()) return Number;
    else if(value.isString()) return String;
    else if(value.isArray()) return Array;
    else if(value.isObject()) return Object;
    return Undefined;
}

DesignerPropertiesPanelWidget::ScriptValueType DesignerPropertiesPanelWidget::getScriptValuePropertyType(const QScriptValue& value, QString propertyName)
{
    QString typeOfProperty = QString("#") + propertyName;
    if(value.property(typeOfProperty).isString())
    {
        for(int i=0; i < scriptValueUserTypeList.count(); i++)
        {
            return (ScriptValueType)(User+i);
        }
    }
    return getScriptValueType(value.property(propertyName));
}

void DesignerPropertiesPanelWidget::addPropertyItems(QScriptValue value, int maxLevel, QTreeWidgetItem* parentItem)
{
    ScriptValueType valueType = getScriptValueType(value);
    QStringList valueList;

    QList<QTreeWidgetItem *> newItems;

    switch(valueType)
    {
    case Null:
    case Boolean:
    case Number:
    case String:
        if(!parentItem)
        {
            valueList << " <Value>" << formatScriptValue(value, maxLevel);
            newItems.append(new QTreeWidgetItem(valueList));
        }
        break;
    case Array:
    {
        if(maxLevel>=0)
        {
            int length = value.property("length").toInt32();
            for(int i=0; i<length; i++)
            {
                QStringList fieldList;
                fieldList<<QString(" [%1]").arg(i)<<formatScriptValue(value.property(i), maxLevel);
                QTreeWidgetItem* childItem = new QTreeWidgetItem(fieldList);
                addPropertyItems(value.property(i), maxLevel-1, childItem);
                newItems.append(childItem);
            }
        }
        break;
    }
    case Object:
    {
        if(maxLevel>=0)
        {
            QScriptValueIterator propItr(value);
            while(propItr.hasNext())
            {
                propItr.next();

                if(propItr.name().mid(0,1)=="$") //type info, skip
                {
                    continue;
                }

                QStringList valueList;
                valueList<<propItr.name();

                QScriptValue typeNameValue = value.property(QString("$")+propItr.name());
                if(typeNameValue.isString())
                {

                }
                else
                {
                    valueList<<formatScriptValue(propItr.value(), maxLevel);
                    QTreeWidgetItem *objectItem =  new QTreeWidgetItem(valueList);
                    addPropertyItems(propItr.value(), maxLevel-1, objectItem);
    //                newItems.append(insertArrayItems(new QTreeWidgetItem(valueList),propItr.value()));
                    newItems.append(objectItem);

                }
            }
        }
        break;
    }
    default:
        break;
    }

    if(parentItem)
    {
        parentItem->addChildren(newItems);
    }
    else
    {
        propertiesWidget->addTopLevelItems(newItems);
    }
}


QString DesignerPropertiesPanelWidget::formatScriptValue(QScriptValue value, int maxLevel)
{
    switch(getScriptValueType(value))
    {
    case Undefined:
        return " <Undefined> ";
    case Null:
        return " <Null> ";
    case Boolean:
    case Number:
    case String:
        return value.toString();
    case Array:
        if(maxLevel>0)
        {
            return " <Array>";
        }
        else
        {
            QString result = "{";
            int length = value.property("length").toInt32();
            for(int i=0;i<length;i++)
            {
                if(i) result+=", ";
                result+=formatScriptValue(value.property(i), maxLevel-1);
            }
            result+="}";
            return result;
        }
    case Object:
        if(maxLevel>0)
        {
            return " <Compound-object>";
        }
        else
        {
            QString result = "{";
            bool hasOutput = false;
            QScriptValueIterator propItr(value);
            while(propItr.hasNext())
            {
                propItr.next();
                if(hasOutput)
                {
                    result+="; ";
                }
                hasOutput=true;
                result+= propItr.name();
                result+= "=";
                result+= formatScriptValue(propItr.value(), maxLevel-1);
            }
            result+="}";

            return result;
        }
    default:
        return " <Unknown>";
    }
}

void DesignerPropertiesPanelWidget::updateTarget(QScriptValue value)
{
    ScriptValueType valueType = getScriptValueType(value);

    if(valueType==Undefined)
    {
        invalidWidget->show();
        propertiesWidget->hide();
        cached = QScriptValue(QScriptValue::UndefinedValue);
        return;
    }
    else
    {
        if(!cached.strictlyEquals(value))
        {
            propertiesWidget->clear();

            addPropertyItems(value, 1, NULL);
        }
        propertiesWidget->expandAll();

        invalidWidget->hide();
        propertiesWidget->show();
    }
}
