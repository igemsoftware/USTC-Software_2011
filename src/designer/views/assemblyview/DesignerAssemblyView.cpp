#include "DesignerAssemblyView.h"
#include "ui_DesignerAssemblyView.h"

namespace AssemblyViewNameSpace
{
    QScriptEngine * engine = 0;
    QList<QString> partTypes;

}
using namespace AssemblyViewNameSpace;


AssemblyView::AssemblyView(QWidget *parent, DesignerMainWnd *mainWnd) :
    DesignerViewItf(parent, mainWnd),
    ui(new Ui::AssemblyView)
{
    ui->setupUi(this);

    if( !engine )
    {
        engine = new QScriptEngine;
        partTypes.clear();
        partTypes.push_back("prom");
        partTypes.push_back("rbs");
        partTypes.push_back("pcs");
        partTypes.push_back("term");
        partTypes.push_back("NULL");
    }

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
    searchWidget->setFixedWidth(200);
    propertyWidget->setFixedWidth(200);
    hLayout->addLayout(vLayout);
    hLayout->addLayout(rvLayout);



    ui->tabAssemblyView->setLayout( hLayout );

    connect( mainScene , SIGNAL(setScriptValue(QScriptValue)) , propertyWidget , SLOT(changeScriptValue(QScriptValue)) );

}

AssemblyView::~AssemblyView()
{
    delete ui;
}
