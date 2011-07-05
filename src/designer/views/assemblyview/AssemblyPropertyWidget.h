#ifndef ASSEMBLYPROPERTYWIDGET_H
#define ASSEMBLYPROPERTYWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QLayout>

class AssemblyPropertyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AssemblyPropertyWidget(QWidget *parent = 0);

signals:

public slots:

private:
    QTreeWidget * treeView;
};

#endif // ASSEMBLYPROPERTYWIDGET_H
