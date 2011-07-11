#ifndef DESIGNERPROPERTIESPANELWIDGET_H
#define DESIGNERPROPERTIESPANELWIDGET_H

#include <QtScript>
#include <QtGui>

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
        Unknown
    };

    ScriptValueType getScriptValueType(QScriptValue& value);
    QString formatScriptValue(QScriptValue value);
    QTreeWidgetItem* insertArrayItems(QTreeWidgetItem* item, QScriptValue value);

protected:
    QTreeWidget*  propertiesWidget;
    QLabel*       invalidWidget;

    QScriptValue  cached;

signals:

public slots:
    void updateTarget(QScriptValue value);

};

#endif // DESIGNERPROPERTIESPANELWIDGET_H
