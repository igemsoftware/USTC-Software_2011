#ifndef DESIGNERNETWORKVIEW_H
#define DESIGNERNETWORKVIEW_H

#include <QWidget>
#include <DesignerViewItf.h>

#include <DesignerNetworkView_SBMLHighlighter.h>

namespace Ui {
    class NetworkView;
}

class NetworkView : public DesignerViewItf
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit NetworkView(QWidget *parent = 0);
    ~NetworkView();

private:
    Ui::NetworkView *ui;
    NetworkView_SBMLHighlighter *sbmlHighlighter;
};

#endif // DESIGNERNETWORKVIEW_H
