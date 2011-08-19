#include "AssemblyView.h"

#include "common/mainwnd/DesignerMainWnd.h"
#include "interfaces/DesignerModelItf.h"
#include "models/reactionnetworkmodel/ReactionNetworkDataTypes.h"
#include "AssemblyDBEditor.h"

namespace AssemblyViewNameSpace
{
    bool firstInstance = true;
    QList<QString> partTypes;

}
using namespace AssemblyViewNameSpace;
using namespace ReactionNetworkDataTypes;


AssemblyView::AssemblyView(DesignerMainWnd *mainWnd, DesignerModelItf *model) :
    DesignerViewItf(mainWnd, model)
{
    if( firstInstance )
    {
        firstInstance = false;
        partTypes.clear();
        partTypes.push_back("prom");
        partTypes.push_back("rbs");
        partTypes.push_back("pcs");
        partTypes.push_back("term");
        partTypes.push_back("NULL");
    }

    engine = mainWindow->getCurrentModel()->getEngine();

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

    connect( mainScene , SIGNAL(setScriptValue(QScriptValue)) , propertyWidget , SLOT(changeScriptValue(QScriptValue)) );
    connect( mainScene , SIGNAL(setScriptValue(QScriptValue)) , mainWnd->getPanelWidget("PropertiesPanel") , SLOT(updateTarget(QScriptValue)) );
}

AssemblyView::~AssemblyView()
{
    delete mainScene;
}

QString AssemblyView::outputMoDeLText()
{
    return mainScene->outputMoDeLText();
}
