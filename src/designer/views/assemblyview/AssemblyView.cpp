#include <QSplitter>
#include "AssemblyView.h"
#include "common/mainwnd/DesignerMainWnd.h"
#include "interfaces/DesignerModelItf.h"
#include "models/reactionnetworkmodel/ReactionNetworkDataTypes.h"
#include "AssemblyDBEditor.h"
#include "common/app/DesignerApp.h"

using namespace ReactionNetworkDataTypes;


AssemblyView::AssemblyView(DesignerMainWnd *mainWnd, DesignerModelComponent *model) :
    DesignerViewComponent(mainWnd, model)
{

    AssemblyPropertyEditor::initializeOnce();
    engine = mainWindow->getCurrentModel()->getEngine();

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

    mainScene->readModel();

    connect( mainScene , SIGNAL(setScriptValue(QScriptValue)) , mainWnd->getPanelWidget("PropertiesPanel") , SLOT(updateTarget(QScriptValue)) );



    igameDBRefresh();
}

AssemblyView::~AssemblyView()
{
    delete mainScene;
}

QString AssemblyView::outputMoDeLText()
{
    return mainScene->outputMoDeLText(mainWindow->getCurrentModel());
}

void AssemblyView::igameDBRefresh()
{
    QSqlDatabase db = QSqlDatabase::database("igame");
    QSqlQuery query(db);
    query.exec("SHOW TABLES");
    QList<QScriptValue> * combo = new QList<QScriptValue>;
    while( query.next() )
    {
        if( query.value(0).toString() == "function" ||
            query.value(0).toString() == "inducer" ||
            query.value(0).toString() == "agent" ) continue;
        combo->push_back( QScriptValue( query.value(0).toString() ) );
    }
    AssemblyPropertyEditor::setCombo( "compartmentType" , combo );

    mainScene->igameDBRefresh();
    searchWidget->reload();
}

void AssemblyView::updateFeatureToolbar(QToolBar *toobar)
{
    QIcon text_icon(":/designer/assemblyview/text_editor.png");
    toobar->addAction(text_icon, "Text", mainScene, SLOT(launchTextEditor()));
    QIcon param_icon(":/designer/assemblyview/param_editor.png");
    toobar->addAction(param_icon, "Param", mainScene, SLOT(requestParameterEdit()));
    QIcon event_icon(":/designer/assemblyview/event_editor.png");
    toobar->addAction(event_icon, "Event", mainScene, SLOT(requestEventEdit()));

    toobar->addSeparator();
    QIcon run_icon(":/designer/assemblyview/start.png");
    toobar->addAction(run_icon, "Run", this, SLOT(CallIGame()));
}

void AssemblyView::CallIGame()
{
    int ans = QMessageBox::question(0, tr("Save"),
                          tr("To proceed, you have to save the current model to file \"%1\"\n"
                             "Do you want to overwrite it?")
                             .arg(mainWindow->getCurrentDoc()->getDocumentFileInfo().absoluteFilePath())
                          , QMessageBox::Yes | QMessageBox::Cancel);
    if( ans == QMessageBox::Yes )
    {
        mainWindow->on_actionFileSave_triggered();
    }else return;

    QList<QString> args;
    args.append( DesignerApp::instance()->readConfigValue("external.paths","MoDeL","").toString() );
    if( args[0].isEmpty() )
    {
        QString model_path = QFileDialog::getOpenFileName(0, "Select MoDeL.pl", QDir::homePath(), "MoDeL (MoDeL.pl)");
        if( !model_path.endsWith("MoDeL.pl") )
        {
            QMessageBox::critical(0, tr("Error"), tr("Please select MoDeL.pl"));
            return;
        }
        DesignerApp::instance()->writeConfigValue("external.paths","MoDeL",model_path);
        args[0] = model_path;
    }
    args.append(mainWindow->getCurrentDoc()->getDocumentFileInfo().fileName());
    QFSFileEngine::setCurrentPath(mainWindow->getCurrentDoc()->getDocumentFileInfo().absolutePath());

    int status = QProcess::execute("perl", args);
    if( status != 0 )
    {
        QMessageBox::critical(0, tr("Error"), tr("An error occured while executing MoDeL.pl.\nPlease check if perl or MoDeL is broken.\nError code:%1").arg(status));
        return;
    }
    DesignerMainWnd *newWnd = DesignerMainWnd::globalCreateNewMainWnd();
    QString sbml_file = mainWindow->getCurrentDoc()->getDocumentFileInfo().fileName();
    sbml_file.chop(6);
    sbml_file.append(".xml");
    newWnd->openFile(sbml_file);
}
