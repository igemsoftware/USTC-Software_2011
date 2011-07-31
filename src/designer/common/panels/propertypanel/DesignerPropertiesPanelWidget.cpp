#include <QtScript>
#include <QtVariantEditorFactory>
#include <QtTreePropertyBrowser>

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
    variantManager = new QtVariantPropertyManager();

    variantFactory = new QtVariantEditorFactory();
    propertiesWidget = new QtTreePropertyBrowser(this);
    propertiesWidget->setFactoryForManager(variantManager, variantFactory);
//    propertiesWidget->setPropertiesWithoutValueMarked(true);
//    propertiesWidget->setRootIsDecorated(true);
    propertiesWidget->show();

    gridLayout->addWidget(propertiesWidget, 0, 0, 1, 1);

//    updateTarget(QScriptValue(QScriptValue::UndefinedValue));
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

QVariant::Type DesignerPropertiesPanelWidget::getQVariantTypeForScriptValueType(DesignerPropertiesPanelWidget::ScriptValueType type)
{
    if(type==Undefined || type==Null) return QVariant::Invalid;//(QVariant::Type)QtVariantPropertyManager::groupTypeId();
    else if(type==Boolean) return QVariant::Bool;
    else if(type==Number)  return QVariant::Double;
    else if(type==String)  return QVariant::String;
    return (QVariant::Type)QtVariantPropertyManager::groupTypeId();
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

void DesignerPropertiesPanelWidget::addPropertyItems(QScriptValue value, int maxLevel, QtProperty* parentItem)
{
    ScriptValueType valueType = getScriptValueType(value);
    QStringList valueList;

    QList<QtProperty*> newProperties;
//    QtProperty *topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
//                QLatin1String(" Group Property"));




    switch(valueType)
    {
    case Null:
    case Boolean:
    case Number:
    case String:
    {
        if(!parentItem)
        {
            QVariant::Type propType = getQVariantTypeForScriptValueType(getScriptValueType(value));
            QtVariantProperty *item;
            if(propType==QVariant::Invalid)
                item = variantManager->addProperty(QVariant::String, " <Value>");
            else
                item = variantManager->addProperty(propType, " <Value>");
            item->setValue(value.toVariant());
            newProperties.append(item);
        }
    }
    case Array:
    {
        if(maxLevel>=0)
        {
            int length = value.property("length").toInt32();
            for(int i=0; i<length; i++)
            {
                QtVariantProperty *item = variantManager->addProperty(QVariant::String, QString(" [%1]").arg(i));
                item->setValue(formatScriptValue(value.property(i), maxLevel));
                addPropertyItems(value.property(i), maxLevel-1, item);
                newProperties.append(item);
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
/*                if(typeNameValue.isString())
                {

                }
                else*/
                {
                    QtVariantProperty *item;
                    QVariant::Type propType = getQVariantTypeForScriptValueType(getScriptValuePropertyType(value, propItr.name()));
                    if(propType==QVariant::Invalid)
                    {
                        item = variantManager->addProperty(
                                QVariant::String, propItr.name());
                        item->setEnabled(false);
                    }
                    else if(propType==(QVariant::Type)QtVariantPropertyManager::groupTypeId() && maxLevel<=0)
                    {
                        item = variantManager->addProperty(
                                QVariant::String, propItr.name());
                    }
                    else
                    {
                        item = variantManager->addProperty(
                                propType, propItr.name());
                    }
                    item->setValue(formatScriptValue(propItr.value(), maxLevel));
//                    item->setEnabled(false);

                    addPropertyItems(propItr.value(), maxLevel-1, item);
                    newProperties.append(item);
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
        for(int i=0;i<newProperties.count();i++)
            parentItem->addSubProperty(newProperties[i]);
    }
    else
    {
        for(int i=0;i<newProperties.count();i++)
            propertiesWidget->addProperty(newProperties[i]);
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
            variantManager->clear();
            propertiesWidget->clear();
            addPropertyItems(value, 3, NULL);
        }

        invalidWidget->hide();
        propertiesWidget->show();
    }
}

void DesignerPropertiesPanelWidget::refreshTarget()
{
    QScriptValue newValue = cached;
    cached = QScriptValue(QScriptValue::UndefinedValue);
    updateTarget(newValue);
}
