#include "DesignerAssemblyView.h"
#include "ui_DesignerAssemblyView.h"

namespace AssemblyViewNameSpace
{
    QScriptEngine * engine = 0;
}

AssemblyView::AssemblyView(QWidget *parent) :
    DesignerViewItf(parent),
    ui(new Ui::AssemblyView)
{
    ui->setupUi(this);

    if( !engine ) engine = new QScriptEngine;

    QHBoxLayout * hLayout = new QHBoxLayout;
    QVBoxLayout * vLayout = new QVBoxLayout;
    QVBoxLayout * rvLayout = new QVBoxLayout;

    vLayout->addWidget( toolBox = new QTabWidget );
    toolBox->setFixedHeight( 50 );
    toolBox->setTabPosition( QTabWidget::South );

    QToolBar * standard = new QToolBar;
    toolBox->addTab( standard , tr("Standard Modules"));
    //will be fixed soon
    standard->addWidget( new AssemblyCreateAndDrag( AssemblyItemCompartment::MimeFormat , tr("Compartment") ) );
    standard->addWidget( new AssemblyCreateAndDrag( AssemblyItemPlasmid::MimeFormat , tr("Plasmid") ) );
    standard->addWidget( new AssemblyCreateAndDrag( AssemblyItemPart::MimeFormat , tr("Brick") ) );

    recentModule = new QToolBar;
    toolBox->addTab( recentModule , tr("Recent Modules") );

    vLayout->addWidget( mainView = new QGraphicsView( mainScene = new AssemblyScene ) );

    rvLayout->addWidget( searchWidget = new AssemblySearchWidget );
    rvLayout->addWidget( propertyWidget = new AssemblyPropertyWidget );

    hLayout->addLayout(vLayout);
    hLayout->addLayout(rvLayout);


    ui->tabAssemblyView->setLayout( hLayout );

}

AssemblyView::~AssemblyView()
{
    delete ui;
}
