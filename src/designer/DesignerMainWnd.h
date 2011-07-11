#ifndef DESIGNERMAINWND_H
#define DESIGNERMAINWND_H

#include "DesignerDebug.h"
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

public slots:
    void createView(QString viewName, bool isProtected = false);

    void openFile(QString& fileName);

    DesignerDocItf * getCurrentDoc(QString defaultDocType = QString());

public:
    QWidget* getPanelWidget(QString panelName);

protected:
    virtual void resizeEvent ( QResizeEvent * event );
    virtual void closeEvent  ( QCloseEvent  * event );

protected:
    void updateTabInfo();

private:
    DesignerDocItf* currentDoc;

private:
    Ui::DesignerMainWnd *ui;

public slots:
    void on_actionFileNew_triggered();
    void on_actionFileExit_triggered();
    void on_actionFileOpen_triggered();

public:
    static DesignerMainWnd* globalCreateNewMainWnd();
    static void globalUnregisterMainWnd(DesignerMainWnd*);
    static QList<DesignerMainWnd*> mainWnd_list;
private slots:
    void on_actionFileSave_triggered();
    void on_tabWidget_tabCloseRequested(int index);
};

#endif // DESIGNERMAINWND_H
