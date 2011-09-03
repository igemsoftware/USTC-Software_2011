#include <QSplitter>
#include "AssemblyView.h"
#include "common/mainwnd/DesignerMainWnd.h"
#include "interfaces/DesignerModelItf.h"
#include "models/reactionnetworkmodel/ReactionNetworkDataTypes.h"
#include "AssemblyDBEditor.h"


using namespace ReactionNetworkDataTypes;


AssemblyView::AssemblyView(DesignerMainWnd *mainWnd, DesignerModelItf *model) :
    DesignerViewItf(mainWnd, model)
{


    engine = mainWindow->getCurrentModel()->getEngine();
/*
    QHBoxLayout * hLayout = new QHBoxLayout;
    QVBoxLayout * vLayout = new QVBoxLayout;
    QVBoxLayout * rvLayout = new QVBoxLayout;

    vLayout->addWidget( toolBox = new QTabWidget );
    toolBox->setFixedHeight( 50 );
    toolBox->setTabPosition( QTabWidget::South );

    QToolBar * standard = new QToolBar;
    toolBox->addTab( standard , tr("Standard Modules"));
    //will be fixed soon
    Compartment sCompartment;
    QScriptValue compartment = Compartment::toScriptValue(engine,sCompartment);
    compartment.setProperty("id","Compartment");
    standard->addWidget( new AssemblyCreateAndDrag( AssemblyItemCompartment::MimeFormat , compartment ) );

    Species sSpecies;
    QScriptValue species = Species::toScriptValue(engine,sSpecies);
    species.setProperty("id","Plasmid");
    standard->addWidget( new AssemblyCreateAndDrag( AssemblyItemPlasmid::MimeFormat , species ) );

    Part sPart;
    QScriptValue part = Part::toScriptValue(engine,sPart);
    part.setProperty("agent","prom");
    standard->addWidget( new AssemblyCreateAndDrag( AssemblyItemPart::MimeFormat , part ) );

    recentModule = new QToolBar;
    toolBox->addTab( recentModule , tr("Recent Modules") );

    vLayout->addWidget( mainView = new QGraphicsView( mainScene = new AssemblyScene( dynamic_cast<IGameModel*>( mainWindow->getCurrentModel() ) , this ) ) );

    rvLayout->addWidget( searchWidget = new AssemblySearchWidget(engine) );
    rvLayout->addWidget( propertyWidget = new AssemblyPropertyWidget );
    searchWidget->setFixedWidth(200);
    propertyWidget->setFixedWidth(200);
    hLayout->addLayout(vLayout);
    hLayout->addLayout(rvLayout);



    this->setLayout( hLayout );
*/
    QSplitter * splitter = new QSplitter;
    splitter->setContentsMargins( 0 , 0 , 0 , 0 );
    splitter->setOrientation(Qt::Vertical);

    QWidget * topWidget = new QWidget;

    QVBoxLayout * vlayout = new QVBoxLayout;
    vlayout->setContentsMargins(1,1,1,1);

    QSize size;
    size.setWidth(48);
    size.setHeight(48);

    Compartment sCompartment;
    QScriptValue compartment = Compartment::toScriptValue(engine,sCompartment);
    compartment.setProperty("id","Compartment");
    compartment.setProperty( "type" , "flask" );
    AssemblyCreateAndDrag * compButton = new AssemblyCreateAndDrag( AssemblyItemCompartment::MimeFormat , compartment , QPixmap(":designer/assemblyview/icon_compartment.png") );
    compButton->setFixedSize( 50 , 50 );
    compButton->setIconSize( size );
    vlayout->addWidget( compButton );

    Species sSpecies;
    QScriptValue species = Species::toScriptValue(engine,sSpecies);
    species.setProperty( "id" , "Plasmid" );
    species.setProperty( "type" , "plasmid" );
    species.setProperty( "constConcentration" , QScriptValue(false) );
    AssemblyCreateAndDrag * plasButton = new AssemblyCreateAndDrag( AssemblyItemPlasmid::MimeFormat , species , QPixmap(":designer/assemblyview/icon_plasmid.png") ) ;
    plasButton->setFixedSize( 50 , 50 );
    plasButton->setIconSize( size );
    vlayout->addWidget( plasButton );

    QHBoxLayout * hlayout = new QHBoxLayout;
    hlayout->setContentsMargins(0,0,0,0);
    hlayout->addLayout(vlayout);
    hlayout->addWidget( searchWidget = new AssemblySearchWidget(engine,this) );

    topWidget->setLayout(hlayout);

    splitter->addWidget(topWidget);
    splitter->addWidget( mainView = new QGraphicsView( mainScene = new AssemblyScene( dynamic_cast<IGameModel*>( mainWindow->getCurrentModel() ) , this ) ) );

    splitter->setCollapsible(0,false);
    splitter->setCollapsible(1,false);

    QVBoxLayout * layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(splitter);
    setLayout(layout);

    QList<int> tmpSize;
    tmpSize.push_back(100);
    tmpSize.push_back(splitter->size().height()-100);
    splitter->setSizes( tmpSize );

    connect( mainScene , SIGNAL(setScriptValue(QScriptValue)) , mainWnd->getPanelWidget("PropertiesPanel") , SLOT(updateTarget(QScriptValue)) );

    AssemblyPropertyEditor::initializeOnce();


    AssemblyDBEditor dialog;
    dialog.exec();

    igameDBRefresh();
}

AssemblyView::~AssemblyView()
{
    delete mainScene;
}

QString AssemblyView::outputMoDeLText()
{
    return mainScene->outputMoDeLText();
}

void AssemblyView::igameDBRefresh()
{
    QSqlDatabase db = QSqlDatabase::database("igame");
    QSqlQuery query(db);
    query.exec("SELECT id FROM compartment");
    QList<QScriptValue> * combo = new QList<QScriptValue>;
    while( query.next() )
        combo->push_back( QScriptValue( query.value(0).toString() ) );
    AssemblyPropertyEditor::setCombo( "compartmentType" , combo );

    mainScene->igameDBRefresh();
    searchWidget->reload();
}
