#include "DesignerAssemblyView.h"
#include "ui_DesignerAssemblyView.h"

AssemblyView::AssemblyView(QWidget *parent) :
    DesignerViewItf(parent),
    ui(new Ui::AssemblyView)
{
    ui->setupUi(this);

    QVBoxLayout * vLayout = new QVBoxLayout;


    vLayout->addWidget( toolBox = new QTabWidget );
    toolBox->setFixedHeight( 100 );
    toolBox->setTabPosition( QTabWidget::South );

    QToolBar * standard = new QToolBar;
    toolBox->addTab( standard , tr("Standard Modules"));
    standard->addWidget( new AssemblyCreateAndDrag( AssemblyItemCompartment::MimeFormat , tr("compartment") ) );

    recentModule = new QToolBar;
    toolBox->addTab( recentModule , tr("Recent Modules") );

    vLayout->addWidget( mainView = new QGraphicsView( mainScene = new AssemblyScene ) );
    ui->tabAssemblyView->setLayout( vLayout );

    AssemblyItemCompartment * flask1 = new AssemblyItemCompartment( tr("flask1") );
    flask1->setPos( 100 , 200 );

    mainScene->addItem( flask1 );
    mainScene->addRect( 0 , 0 , 50 , 50 );

    //QApplication::sendEvent( mainScene , new QMouseEvent( QEvent::MouseButtonPress , QPoint( 300 , 300 ) , Qt::LeftButton , 0 , 0 ));


}

AssemblyView::~AssemblyView()
{
    delete ui;
}
