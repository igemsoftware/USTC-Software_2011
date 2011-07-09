#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QWidget>

namespace Ui {
    class WelcomeView;
}

class DesignerMainWnd;

class WelcomeView : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeView(QWidget *parent = 0);
    ~WelcomeView();

private:
    Ui::WelcomeView *ui;

public:
    DesignerMainWnd *mainWnd;

private slots:
    void on_buttonCreateBehaviorFile_clicked();
    void on_buttonCreateNetworkFile_clicked();
    void on_buttonCreateAssemblyFile_clicked();
    void on_buttonOpenFile_clicked();
    void on_buttonQuit_clicked();
};

#endif // WELCOMEVIEW_H
