#include <QtGui>
#include <QScriptValue>

#include "NetworkView.h"
#include "ui_NetworkView.h"
#include "NetworkViewGraphicsItem.h"
#include "NetworkViewGraphicsScene.h"
#include "NetworkViewButton.h"
#include "NetworkViewGraphicsSceneEdge.h"

#include "common/app/DesignerApp.h"

#include "interfaces/DesignerModelItf.h"
#include "common/mainwnd/DesignerMainWnd.h"

#include "models/common/ModelSymbol.h"

#include "DesignerDebug.h"
#include "common/panels/propertypanel/DesignerPropertiesPanelWidget.h"
#include "Layouter/lagraphlayouterthread.h"
#include "models/reactionnetworkmodel/ReactionNetworkDataTypes.h"

using namespace ReactionNetworkDataTypes;

NetworkView::NetworkView(DesignerMainWnd *mainWnd, DesignerModelComponent *model) :
    DesignerViewComponent(mainWnd, model),
    ui(new Ui::NetworkView)
{
    ui->setupUi(this);
    engine = mainWindow->getCurrentModel()->getEngine();
    this->selectState="NoNeed";

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

    linebutton=new QPushButton();
    linebutton->setFixedSize(50,50);
    hlayout->addWidget(linebutton);
    linebutton->setFlat(true);
    linebutton->setIcon(*(new QIcon(":/designer/networkview/generate.png")));
    connect(this->linebutton,SIGNAL(clicked()),this,SLOT(on_lineButtonClicked()));

    modbutton=new QPushButton();
    modbutton->setFixedSize(50,50);
    hlayout->addWidget(modbutton);
    modbutton->setFlat(true);
    modbutton->setIcon(*(new QIcon(":/designer/networkview/modify.png")));
    connect(this->modbutton,SIGNAL(clicked()),this,SLOT(on_modButtonClicked()));

    ui->buttons->setLayout(hlayout);
    NetworkViewGraphicsScene *scene = new NetworkViewGraphicsScene(ui->graphicsView);
    scene->model=dynamic_cast<ReactionNetworkModel*>( mainWindow->getCurrentModel());
    scene->loadFromModel(model);
    scene->loaded=true;
    ui->graphicsView->setScene(scene);

    connect(scene, SIGNAL(selectionChanged()), this, SLOT(on_sceneSelectionChanged()));
    connect(scene,SIGNAL(setScriptValue()),this,SLOT(refreshWidget()));
}

NetworkView::~NetworkView()
{
    delete ui;
}

void NetworkView::on_sceneSelectionChanged()
{
    if(dynamic_cast<NetworkViewGraphicsScene *>(ui->graphicsView->scene())->locked || !dynamic_cast<NetworkViewGraphicsScene *>(ui->graphicsView->scene())->loaded)
        return;
    QList<QGraphicsItem*> selectedItem = ui->graphicsView->scene()->selectedItems();    
    foreach( QGraphicsItem* item , ui->graphicsView->scene()->items() )
    {
        if( dynamic_cast<NetworkViewGraphicsItem*>(item) ) dynamic_cast<NetworkViewGraphicsItem*>(item)->loseSelection(selectedItem);
    }
    foreach( QGraphicsItem* item , selectedItem )
    {
        if( dynamic_cast<NetworkViewGraphicsItem*>(item) )
        {
            dynamic_cast<NetworkViewGraphicsItem*>(item)->getSelection();
        }
    }
    if(selectedItem.count()>0&&dynamic_cast<NetworkViewGraphicsSceneNodeSubstance *>(selectedItem.first()))
    {
        if(this->selectState=="NothingE")
        {
            this->substance=dynamic_cast<NetworkViewGraphicsSceneNodeSubstance *>(selectedItem.first());
            this->selectState="SubstanceReadyE";
            this->linebutton->setDown(true);
        }
        else if(this->selectState=="ReactionReadyE")
        {
            this->substance=dynamic_cast<NetworkViewGraphicsSceneNodeSubstance *>(selectedItem.first());
            ui->graphicsView->scene()->addItem(new NetworkViewGraphicsSceneEdge(ui->graphicsView->scene()->activePanel(),this->reaction,this->substance,NetworkViewGraphicsSceneEdge::DirectedEdge));
            dynamic_cast<NetworkViewGraphicsSceneNodeReaction *>(this->reaction)->refreshScriptValue();
            this->selectState="NoNeed";
            this->linebutton->setDown(false);
        }
        else if(this->selectState=="NothingM")
        {
            this->substance=dynamic_cast<NetworkViewGraphicsSceneNodeSubstance *>(selectedItem.first());
            this->selectState="SubstanceReadyM";
            this->modbutton->setDown(true);
        }
    }
    else if(selectedItem.count()>0&&dynamic_cast<NetworkViewGraphicsSceneNodeReaction *>(selectedItem.first()))
    {
        if(this->selectState=="NothingE")
        {
            this->reaction=dynamic_cast<NetworkViewGraphicsSceneNodeReaction *>(selectedItem.first());
            this->selectState="ReactionReadyE";
            this->linebutton->setDown(true);
        }
        else if(this->selectState=="SubstanceReadyE")
        {
            this->reaction=dynamic_cast<NetworkViewGraphicsSceneNodeReaction *>(selectedItem.first());            
            ui->graphicsView->scene()->addItem(new NetworkViewGraphicsSceneEdge(ui->graphicsView->scene()->activePanel(),this->substance,this->reaction,NetworkViewGraphicsSceneEdge::DirectedEdge));
            dynamic_cast<NetworkViewGraphicsSceneNodeReaction *>(selectedItem.first())->refreshScriptValue();
            this->selectState="NoNeed";
            this->linebutton->setDown(false);
        }
        else if(this->selectState=="SubstanceReadyM")
        {
            this->reaction=dynamic_cast<NetworkViewGraphicsSceneNodeReaction *>(selectedItem.first());
            ui->graphicsView->scene()->addItem(new NetworkViewGraphicsSceneModification(ui->graphicsView->scene()->activePanel(),this->substance,this->reaction));
            dynamic_cast<NetworkViewGraphicsSceneNodeReaction *>(selectedItem.first())->refreshScriptValue();
            this->selectState="NoNeed";
            this->modbutton->setDown(false);
        }
    }
    else
    {
        this->selectState="NoNeed";
        this->linebutton->setDown(false);
        this->modbutton->setDown(false);
    }

    if(selectedItem.count()>0)
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

void NetworkView::on_lineButtonClicked()
{
    linebutton->setDown(true);
    ui->graphicsView->scene()->clearSelection();
    this->selectState="NothingE";
}

void NetworkView::on_modButtonClicked()
{
    modbutton->setDown(true);
    ui->graphicsView->scene()->clearSelection();
    this->selectState="NothingM";
}

void NetworkView::refreshWidget()
{
    emit updateSelectedItem(mainWindow->getCurrentModel()->getModel());
}

void NetworkView::updateFeatureToolbar(QToolBar *toolBar)
{
    QString copasiPath = DesignerApp::instance()->readConfigValue("externalapps", "CopasiPath", "").toString();
    if(copasiPath.length())
    {
        QAction *actionInvokeCopasi;
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/designer/common/toolbar/common/applications/copasi.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionInvokeCopasi = toolBar->addAction(icon, "Copasi");
        connect(actionInvokeCopasi, SIGNAL(triggered()), SLOT(on_invokeCopasi()));
    }

}

void NetworkView::on_invokeCopasi()
{
    //Actually you should generate an sbml in temporary folder
    //And invoke CopasiUI.exe with -i <filename>.
    QString copasiPath = DesignerApp::instance()->readConfigValue("externalapps", "CopasiPath", "").toString();
    QMessageBox(QMessageBox::NoIcon, "", copasiPath+"/bin/CopasiUI.exe").exec();
    QProcess::execute(copasiPath+"/bin/CopasiUI.exe", QStringList());
}
