#ifndef DESIGNERWELCOMEDIALOG_H
#define DESIGNERWELCOMEDIALOG_H

#include <QWidget>
#include <DesignerMainWnd.h>

namespace Ui {
    class WelcomeDialog;
}

class WelcomeDialog : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeDialog(QWidget *parent, DesignerMainWnd * mainWnd);
    ~WelcomeDialog();

private:
    DesignerMainWnd *mainWnd;

    Ui::WelcomeDialog *ui;

private slots:
    void on_buttonCreateBehaviorFile_clicked();
    void on_buttonCreateNetworkFile_clicked();
    void on_buttonCreateAssemblyFile_clicked();
    void on_buttonQuit_clicked();
};

#endif // DESIGNERWELCOMEDIALOG_H
