#ifndef DESIGNERMAINWND_H
#define DESIGNERMAINWND_H

#include <QMainWindow>
#include <DesignerViewItf.h>

namespace Ui {
    class DesignerMainWnd;
}

class DesignerMainWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit DesignerMainWnd(QWidget *parent = 0);
    ~DesignerMainWnd();

    void createView(QString viewName);

protected:
    virtual void resizeEvent ( QResizeEvent * event );
    virtual void closeEvent  ( QCloseEvent  * event );

private:
    QWidget* welcomeDialog;
    DesignerViewItf* currentView;

private:
    Ui::DesignerMainWnd *ui;

private slots:
    void on_action_New_File_activated(int );


public:
    static void globalCreateNewMainWnd();
    static void globalUnregisterMainWnd(DesignerMainWnd*);
    static QList<DesignerMainWnd*> mainWnd_list;
};

#endif // DESIGNERMAINWND_H
