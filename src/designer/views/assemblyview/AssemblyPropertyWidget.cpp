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
        if( iter.value().isArray() )
        {
            labels.push_back("");
            QTreeWidgetItem * item = new QTreeWidgetItem(labels);
            QScriptValueIterator innerIter(iter.value());
            QTreeWidgetItem * lastChild = 0;
            while( innerIter.hasNext() )
            {
                innerIter.next();
                labels.clear();
                labels.push_back("name");
                labels.push_back(innerIter.value().property("name").toString());
                item->addChild( lastChild = new QTreeWidgetItem(labels) );
            }
            if( lastChild ) item->removeChild( lastChild ); //dont know why, will be fixed ... probably
            treeWidget->insertTopLevelItem( rowcount++ , item );
        }else
        {
            labels.push_back(iter.value().toString());
            treeWidget->insertTopLevelItem( rowcount++ , new QTreeWidgetItem(labels) );
        }
    }
}
