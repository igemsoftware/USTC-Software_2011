#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QWidget>
#include "interfaces/DesignerViewItf.h"

namespace Ui {
    class WelcomeView;
}

class DesignerMainWnd;

class WelcomeView : public DesignerViewItf
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit WelcomeView(DesignerMainWnd* mainWnd, DesignerModelItf* model);
    ~WelcomeView();
signals:
    void createDocWithViewType(QString);

private slots:
    void on_buttonCreateAssemblyFile_clicked()
    {
        emit createDocWithViewType("AssemblyView");
    }

    void on_buttonCreateNetworkFile_clicked()
    {
        emit createDocWithViewType("NetworkView");
    }

    void on_buttonCreateBehaviorFile_clicked()
    {
        emit createDocWithViewType("BehaviorView");
    }


private:
    Ui::WelcomeView *ui;

};

#endif // WELCOMEVIEW_H
