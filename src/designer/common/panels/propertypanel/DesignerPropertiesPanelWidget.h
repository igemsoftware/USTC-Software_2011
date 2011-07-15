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
    QTreeWidget*  propertiesWidget;
    QtVariantPropertyManager *variantManager;
    QtVariantEditorFactory *variantFactory;
    QtTreePropertyBrowser* propertyBrowser;
    QLabel*       invalidWidget;

    QScriptValue  cached;

signals:

public slots:
    void updateTarget(QScriptValue value);

};

#endif // DESIGNERPROPERTIESPANELWIDGET_H
