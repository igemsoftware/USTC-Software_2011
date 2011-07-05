#include "AssemblySearchWidget.h"
#include "AssemblyLib.h"
#include "AssemblyItemPart.h"

using namespace AssemblyViewNameSpace;

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

}

void AssemblySearchWidget::startDrag(QModelIndex index)
{
    int row = index.row();

    QByteArray itemData(sizeof(QScriptValue*),0);
    QScriptValue * copy = new QScriptValue(partList[row]); //assume we can copy here
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
    tableWidget->clear();
    if( !partList.count() ) return;


    QScriptValueIterator * iter = new QScriptValueIterator( partList.first() );
    int colcount = 0;
    while( iter->hasNext() )
    {
        iter->next();
        colcount++;
    }
    delete iter;
    tableWidget->setColumnCount(colcount);

    iter = new QScriptValueIterator( partList.first() );
    colcount = 0;
    while( iter->hasNext() )
    {
        iter->next();
        QString name = iter->name();
        tableWidget->setHorizontalHeaderItem(colcount, new QTableWidgetItem(name));
        colcount++;
    }
    delete iter;

    tableWidget->setRowCount(partList.count());
    for( int i = 0 ; i < partList.count() ; i++ )
    {
        iter = new QScriptValueIterator( partList[i] );
        colcount = 0;
        while(iter->hasNext())
        {
            iter->next();
            QString value = iter->value().toString();
            tableWidget->setItem( i , colcount , new QTableWidgetItem(value) );
            colcount++;
        }
        delete iter;
    }
}
