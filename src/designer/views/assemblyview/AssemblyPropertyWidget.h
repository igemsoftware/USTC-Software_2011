#ifndef ASSEMBLYPROPERTYWIDGET_H
#define ASSEMBLYPROPERTYWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QLayout>
#include <QScriptEngine>
#include <QScriptValueIterator>

class AssemblyPropertyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AssemblyPropertyWidget(QWidget *parent = 0);

signals:

public slots:
    void changeScriptValue( QScriptValue  value );
private:
    QTreeWidget * treeWidget;
};

#endif // ASSEMBLYPROPERTYWIDGET_H
