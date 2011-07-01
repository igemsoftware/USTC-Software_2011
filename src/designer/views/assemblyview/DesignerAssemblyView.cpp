#include "DesignerAssemblyView.h"
#include "ui_DesignerAssemblyView.h"

AssemblyView::AssemblyView(QWidget *parent) :
    DesignerViewItf(parent),
    ui(new Ui::AssemblyView)
{
    ui->setupUi(this);

    QVBoxLayout * vLayout = new QVBoxLayout;


    vLayout->addWidget( toolBox = new QTabWidget );
    toolBox->setFixedHeight( 50 );
    toolBox->setTabPosition( QTabWidget::South );

    QToolBar * standard = new QToolBar;
    toolBox->addTab( standard , tr("Standard Modules"));
    standard->addWidget( new AssemblyCreateAndDrag( AssemblyItemCompartment::MimeFormat , tr("Compartment") ) );
    standard->addWidget( new AssemblyCreateAndDrag( AssemblyItemPlasmid::MimeFormat , tr("Plasmid") ) );
    standard->addWidget( new AssemblyCreateAndDrag( AssemblyItemPart::MimeFormat , tr("Brick") ) );

    recentModule = new QToolBar;
    toolBox->addTab( recentModule , tr("Recent Modules") );

    vLayout->addWidget( mainView = new QGraphicsView( mainScene = new AssemblyScene ) );
    ui->tabAssemblyView->setLayout( vLayout );

    /*AssemblyItemBase * temp = new AssemblyItemBase( tr("") , tr(":/designer/oops.png") , tr(":designer/oops.png") );
    mainScene->addItem( temp );
    temp->setPos( 0 , 0 );
    temp->show();*/
    //QApplication::sendEvent( mainScene , new QMouseEvent( QEvent::MouseButtonPress , QPoint( 300 , 300 ) , Qt::LeftButton , 0 , 0 ));


}

AssemblyView::~AssemblyView()
{
    delete ui;
}
