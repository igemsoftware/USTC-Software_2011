#ifndef DESIGNERPROPERTIESPANELWIDGET_H
#define DESIGNERPROPERTIESPANELWIDGET_H

#include <QtScript>
#include <QtGui>

class QtVariantPropertyManager;
class QtVariantEditorFactory;
class QtTreePropertyBrowser;
class QtProperty;

class DesignerPropertiesPanelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DesignerPropertiesPanelWidget(QWidget *parent = 0);

    enum ScriptValueType
    {
        Undefined,
        Null,
        Boolean,
        Number,
        String,
        Array,
        Object,
        User
    };

    struct ScriptValueUserType
    {
        QScriptString name;
        void  (*handler)();
    };

    QList<ScriptValueUserType> scriptValueUserTypeList;

    void addPropertyItems(QScriptValue value, int maxLevel, QtProperty* parentItem);
    QString formatScriptValue(QScriptValue value, int maxLevel);

    ScriptValueType getScriptValueType(const QScriptValue& value);
    ScriptValueType getScriptValuePropertyType(const QScriptValue& value, QString propertyName);
    QVariant::Type  getQVariantTypeForScriptValueType(ScriptValueType type);

protected:
    QtVariantPropertyManager *variantManager;
    QtVariantEditorFactory *variantFactory;
    QtTreePropertyBrowser* propertiesWidget;
    QLabel*       invalidWidget;

    QScriptValue  cached;

public slots:
    void updateTarget(QScriptValue value);

};

#endif // DESIGNERPROPERTIESPANELWIDGET_H
