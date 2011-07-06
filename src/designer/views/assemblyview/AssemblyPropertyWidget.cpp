#include "AssemblyPropertyWidget.h"

AssemblyPropertyWidget::AssemblyPropertyWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addWidget( treeWidget = new QTreeWidget );
    setLayout(vLayout);

    QList<QString> labels;
    labels.push_back( "Property" );
    labels.push_back( "Value" );
    treeWidget->setHeaderLabels( labels );
}

void AssemblyPropertyWidget::changeScriptValue( QScriptValue value )
{
    treeWidget->clear();
    QList<QString> labels;
    labels.push_back( "Property" );
    labels.push_back( "Value" );
    treeWidget->setHeaderLabels( labels );

    QScriptValueIterator iter(value);
    int rowcount = 0;
    while( iter.hasNext() )
    {
        iter.next();
        labels.clear();
        labels.push_back(iter.name());
        labels.push_back(iter.value().toString());
        treeWidget->insertTopLevelItem( rowcount++ , new QTreeWidgetItem(labels) );
    }
}
