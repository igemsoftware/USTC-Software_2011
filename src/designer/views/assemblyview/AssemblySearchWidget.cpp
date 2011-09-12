#include "AssemblySearchWidget.h"
#include "AssemblyLib.h"
#include "AssemblyItemPart.h"
#include "AssemblyItemMolecule.h"
#include <QSqlRecord>

using namespace ReactionNetworkDataTypes;

AssemblySearchWidget::AssemblySearchWidget( QScriptEngine * newEngine , QWidget *parent) :
    QWidget(parent) ,
    engine(newEngine)
{
    db = QSqlDatabase::database("igame");
    query = new QSqlQuery(db);

    QVBoxLayout * vLayout = new QVBoxLayout;
    QHBoxLayout * hLayout = new QHBoxLayout;
    vLayout->setContentsMargins(0,0,0,0);
    hLayout->setContentsMargins(0,0,0,0);

    hLayout->addWidget( compartmentCombo = new QComboBox );
    hLayout->addWidget( typeCombo = new QComboBox );
    hLayout->addWidget( lineEdit = new QLineEdit );
    vLayout->addLayout( hLayout );
    vLayout->addWidget( tableWidget = new QTableWidget );

    tableWidget->setSizePolicy( QSizePolicy::Expanding , QSizePolicy::Preferred );
    setLayout( vLayout );


    typeCombo->addItem("ALL");
    typeCombo->addItem("prom");
    typeCombo->addItem("rbs");
    typeCombo->addItem("pcs");
    typeCombo->addItem("term");
    typeCombo->addItem("mol");
    typeCombo->addItem("NULL");

    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode( QAbstractItemView::SingleSelection );
    connect( tableWidget , SIGNAL(pressed(QModelIndex)) , this , SLOT(startDrag(QModelIndex)) );
    connect( typeCombo , SIGNAL(currentIndexChanged(QString)) , this , SLOT(inputChanges(QString)) );
    connect( compartmentCombo , SIGNAL(currentIndexChanged(QString)) , this , SLOT(inputChanges(QString)) );
    connect( lineEdit , SIGNAL(textChanged(QString)) , this , SLOT(inputChanges(QString)) );

    reload();
}

void AssemblySearchWidget::reload()
{
    compartmentCombo->clear();
    QSqlQuery query(db);
    query.exec( "SELECT id FROM compartment" );
    while( query.next() )
        compartmentCombo->addItem( query.value(0).toString() );
}

void AssemblySearchWidget::startDrag(QModelIndex index)
{
    QByteArray itemData(sizeof(QScriptValue*),0);
    QScriptValue * copy = new QScriptValue( engine->newObject() );

    query->seek( index.row() );
    copy->setProperty( "reversed" , QScriptValue(false) );
    copy->setProperty( "sites" , query->value( query->record().indexOf("default_site") ).toString() );

    QDrag * drag = new QDrag(this);
    memcpy( itemData.data() , &copy , sizeof(QScriptValue*) );
    QMimeData * mimeData = new QMimeData;

    copy->setProperty( "agent" , query->value( query->record().indexOf("id") ).toString() );
    copy->setProperty( "compartment", compartmentCombo->currentText() );
    if( query->value( query->record().indexOf("type") ).toString().isEmpty()|| query->value( query->record().indexOf("type") ).toString() == "mol" )
    {
        copy->setProperty( "id" , "Molecule" );
        copy->setProperty( "type" , "molecule" );
        copy->setProperty( "constConcentration" , QScriptValue(false) );
        mimeData->setData( AssemblyItemMolecule::MimeFormat , itemData );
        drag->setPixmap( QPixmap(tr(":/designer/assemblyview/icon_mol.png") ) );
    }else{
        copy->setProperty( "type" , "dna" );
        copy->setProperty( "category" , query->value( query->record().indexOf("type") ).toString() );

        mimeData->setData( AssemblyItemPart::MimeFormat , itemData );
        drag->setPixmap( QPixmap(tr(":/designer/assemblyview/icon_%1.png").arg(copy->property("category").toString()) ) );
    }

    drag->setMimeData( mimeData );
    drag->setHotSpot( QPoint( drag->pixmap().width()/2 , drag->pixmap().height()/2 ) );
    drag->exec();
}

void AssemblySearchWidget::inputChanges(QString)
{
    delete query;
    query = new QSqlQuery(db);
    QString sql;
    if( typeCombo->currentText() == "ALL" )
    {
        sql = tr("SELECT * FROM %1_agent WHERE id LIKE \'%%2%\' ORDER BY id").arg(compartmentCombo->currentText()).arg(lineEdit->text());
    }else if( typeCombo->currentText() == "NULL" )
    {
        sql = tr("SELECT * FROM %1_agent WHERE id LIKE \'%%2%\' AND type IS NULL ORDER BY id").arg(compartmentCombo->currentText()).arg(lineEdit->text());
    }else{
        sql = tr("SELECT * FROM %1_agent WHERE id LIKE \'%%2%\' AND type = \'%3\' ORDER BY id").arg(compartmentCombo->currentText()).arg(lineEdit->text()).arg(typeCombo->currentText());
    }
    qDebug() << sql;
    qDebug() << query->exec( sql );
    int colCount = 0;
    while( !query->record().fieldName(colCount).isEmpty() ) colCount++;
    tableWidget->setColumnCount(colCount);
    tableWidget->setRowCount( query->numRowsAffected() );
    for( int i = 0 ; i < colCount ; i++ ) tableWidget->setHorizontalHeaderItem( i , new QTableWidgetItem(query->record().fieldName(i)) );
    int i = 0;
    while( query->next() )
    {
        for( int j = 0 ; j < colCount ; j++ ) tableWidget->setItem( i , j , new QTableWidgetItem( query->value(j).toString() ) );
        i++;
    }
}
