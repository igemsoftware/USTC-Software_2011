#include <QtScript>

#include "interfaces/DesignerViewItf.h"
#include "interfaces/DesignerModelItf.h"

#include "PartView.h"
#include "ui_partview.h"
#include "DesignerMainWnd.h"

PartView::PartView(DesignerMainWnd *mainWnd, DesignerModelItf *model) :
    DesignerViewItf(mainWnd, model),
    ui(new Ui::PartView)
{
    ui->setupUi(this);

    connect(this, SIGNAL(updateSelectedItem(QScriptValue)),  mainWindow->getPanelWidget("PropertiesPanel"), SLOT(updateTarget(QScriptValue)));

    emit updateSelectedItem(model->getModel());

}

PartView::~PartView()
{
    delete ui;
}
