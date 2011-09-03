#include <QtGui>
#include "NetworkView.h"

#include "NetworkViewGraphicsItem.h"
#include "NetworkViewGraphicsScene.h"

#include "interfaces/DesignerModelItf.h"
#include "common/mainwnd/DesignerMainWnd.h"

#include "models/common/ModelSymbol.h"

#include "DesignerDebug.h"
#include "ui_NetworkView.h"
#include "common/panels/propertypanel/DesignerPropertiesPanelWidget.h"
#include "Layouter/lagraphlayouterthread.h"
#include <QScriptValue>
#include "models/reactionnetworkmodel/ReactionNetworkDataTypes.h"
#include "NetworkViewButton.h"

using namespace ReactionNetworkDataTypes;

NetworkView::NetworkView(DesignerMainWnd *mainWnd, DesignerModelItf *model) :
    DesignerViewItf(mainWnd, model),
    ui(new Ui::NetworkView)
{
    /*QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    ui->graphicsView = new QGraphicsView(this);
    ui->graphicsView->setStyleSheet("QGraphicsView { border-style: none; }");
    gridLayout->addWidget(graphicsView,1,0,1,1);
    gridLayout->addWidget(buttons,0,1,2,2);*/
    ui->setupUi(this);
    engine = mainWindow->getCurrentModel()->getEngine();
    QHBoxLayout * hlayout = new QHBoxLayout;
    hlayout->setAlignment(Qt::AlignLeft);
    hlayout->setContentsMargins(0,0,0,0);

    Compartment sCompartment;
    QScriptValue compartment = Compartment::toScriptValue(engine,sCompartment);
    compartment.setProperty("id","Compartment");
    compartment.setProperty( "type" , "flask" );
    NetworkViewButton *combutton=new NetworkViewButton("compartment", compartment , QPixmap(":designer/assemblyview/icon_compartment.png"));
    hlayout->addWidget(combutton);

    Species sSpecies;
    QScriptValue species = Species::toScriptValue(engine,sSpecies);
    species.setProperty( "id" , "substance" );
    species.setProperty( "type" , "substance" );
    species.setProperty( "constConcentration" , QScriptValue(false) );
    NetworkViewButton *subbutton=new NetworkViewButton("substance", species , QPixmap(":designer/assemblyview/icon_protein.png"));
    hlayout->addWidget(subbutton);

    Reaction sReaction;
    QScriptValue reaction = Reaction::toScriptValue(engine,sReaction);
    reaction.setProperty( "id" , "reaction" );
    reaction.setProperty( "type" , "reaction" );
    NetworkViewButton *reabutton=new NetworkViewButton("reaction", reaction , QPixmap(":designer/assemblyview/icon_mol.png"));
    hlayout->addWidget(reabutton);

    ui->buttons->setLayout(hlayout);
    NetworkViewGraphicsScene *scene = new NetworkViewGraphicsScene(ui->graphicsView);
    scene->clearScene();    
    scene->loadFromModel(model);
    ui->graphicsView->setScene(scene);

    connect(scene, SIGNAL(selectionChanged()), this, SLOT(on_sceneSelectionChanged()));

    emit on_sceneSelectionChanged();
}

NetworkView::~NetworkView()
{
    delete ui;
}

void NetworkView::on_sceneSelectionChanged()
{
    QList<QGraphicsItem*> selectedItem = ui->graphicsView->scene()->selectedItems();
    if(selectedItem.count()==1)
    {
        NetworkViewGraphicsItem* item = dynamic_cast<NetworkViewGraphicsItem*>(selectedItem.first());
        if(item)
        {
            emit updateSelectedItem(item->itemObject);
            return;
        }
    }
    emit updateSelectedItem(mainWindow->getCurrentModel()->getModel());
}
