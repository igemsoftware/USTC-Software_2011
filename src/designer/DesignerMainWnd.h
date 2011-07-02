#ifndef DESIGNERMAINWND_H
#define DESIGNERMAINWND_H

#include <QMainWindow>
#include "DesignerDocItf.h"
#include "DesignerViewItf.h"

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
    void openFileDialog(void);

    void openFile(QString& fileName);

protected:
    virtual void resizeEvent ( QResizeEvent * event );
    virtual void closeEvent  ( QCloseEvent  * event );

private:
    QWidget* welcomeDialog;
    DesignerViewItf* currentView;
    DesignerDocItf* currentDoc;

private:
    Ui::DesignerMainWnd *ui;

private slots:
    void on_action_New_File_activated(int );
    void on_action_Open_File_triggered();

public:
    static DesignerMainWnd* globalCreateNewMainWnd();
    static void globalUnregisterMainWnd(DesignerMainWnd*);
    static QList<DesignerMainWnd*> mainWnd_list;
};

#endif // DESIGNERMAINWND_H
