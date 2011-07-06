#include "AssemblySearchWidget.h"
#include "AssemblyLib.h"
#include "AssemblyItemPart.h"

using namespace AssemblyViewNameSpace;
using namespace ReactionNetworkDataTypes;

AssemblySearchWidget::AssemblySearchWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout * vLayout = new QVBoxLayout;
    QHBoxLayout * hLayout = new QHBoxLayout;

    hLayout->addWidget( comboBox = new QComboBox );
    hLayout->addWidget( lineEdit = new QLineEdit );
    vLayout->addLayout( hLayout );
    vLayout->addWidget( tableWidget = new QTableWidget );

    setLayout( vLayout );

    comboBox->addItem("ALL");
    comboBox->addItems(partTypes);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect( tableWidget , SIGNAL(pressed(QModelIndex)) , this , SLOT(startDrag(QModelIndex)) );
    connect( comboBox , SIGNAL(currentIndexChanged(QString)) , this , SLOT(inputChanges(QString)) );
    connect( lineEdit , SIGNAL(textChanged(QString)) , this , SLOT(inputChanges(QString)) );

    QList<PropertyDescriptor> properties = Part::listProperty();
    tableWidget->setColumnCount(properties.count());
    int colcount = 0;
    foreach( PropertyDescriptor property , properties )
    {
        tableWidget->setHorizontalHeaderItem(colcount, new QTableWidgetItem(property.property));
        propertyColumn.insert( property.property , colcount );
        colcount++;
    }
}

void AssemblySearchWidget::startDrag(QModelIndex index)
{
    int row = index.row();

    QByteArray itemData(sizeof(QScriptValue*),0);
    QScriptValue * copy = new QScriptValue(engine->newObject());

    QScriptValueIterator iter(partList[row]);
    while( iter.hasNext() )
    {
        iter.next();
        copy->setProperty( iter.name() , iter.value() );
    }

    memcpy( itemData.data() , &copy , sizeof(QScriptValue*) );
    QMimeData * mimeData = new QMimeData;
    mimeData->setData( AssemblyItemPart::MimeFormat , itemData );

    QDrag * drag = new QDrag(this);
    drag->setMimeData( mimeData );
    drag->setPixmap( QPixmap(tr(":/designer/oops.png") ) );
    drag->setHotSpot( QPoint( drag->pixmap().width()/2 , drag->pixmap().height()/2 ) );
    drag->exec();
}

QScriptValueList AssemblySearchWidget::query( QString type , QString name )
{
    QScriptValue temp = engine->newObject();
    temp.setProperty("name",name);
    temp.setProperty("type",type);
    QScriptValueList list;
    list.push_back(temp);
    return list;
}

void AssemblySearchWidget::inputChanges(QString)
{
    partList = query( comboBox->currentText() , lineEdit->text() );
    tableWidget->setRowCount(0);
    if( !partList.count() ) return;

    tableWidget->setRowCount(partList.count());
    for( int i = 0 ; i < partList.count() ; i++ )
    {
        QScriptValueIterator  *iter = new QScriptValueIterator( partList[i] );
        while(iter->hasNext())
        {
            iter->next();
            tableWidget->setItem( i , propertyColumn.value(iter->name()) , new QTableWidgetItem(iter->value().toString()) );
        }
        delete iter;
    }
}
