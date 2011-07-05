#include "AssemblyPropertyWidget.h"

AssemblyPropertyWidget::AssemblyPropertyWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addWidget( treeView = new QTreeView );
    setLayout(vLayout);
}
