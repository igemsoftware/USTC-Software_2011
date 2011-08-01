#ifndef DESIGNERMAINWND_H
#define DESIGNERMAINWND_H

#include "DesignerDebug.h"
#include <QMainWindow>
#include "interfaces/DesignerDocItf.h"
#include "interfaces/DesignerViewItf.h"

namespace Ui {
    class DesignerMainWnd;
}

class DesignerMainWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit DesignerMainWnd(QWidget *parent = 0);
    ~DesignerMainWnd();

public:
    void openFile(QString& fileName);
    void saveFile(QString& fileName, QString docTypeName);

public slots:
    void createModelWithView(QString viewName);


    DesignerDocItf * getCurrentDoc(QString defaultDocType = QString());

public:
    QWidget* getPanelWidget(QString panelName);

public:
    void createView(QString viewName, bool isProtected = false);
    void createView(QString viewName, bool isProtected, DesignerModelItf* model);

protected:
    virtual void resizeEvent ( QResizeEvent * event );
    virtual void closeEvent  ( QCloseEvent  * event );

protected:
    void updateTabInfo();
public:
    void removeTabWithClass(QString className);

private:
    DesignerModelItf* currentModel;
public:
    DesignerModelItf* getCurrentModel() { return currentModel; }
private:
    Ui::DesignerMainWnd *ui;

public slots:
    void on_actionFileNew_triggered();
    void on_actionFileExit_triggered();
    void on_actionFileOpen_triggered();
    void on_actionFileSave_triggered();
    void on_actionHelpAboutApp_triggered();

    void instanceMessageReceived(const QString& message);

public:
    static DesignerMainWnd* globalCreateNewMainWnd();
    static void globalUnregisterMainWnd(DesignerMainWnd*);
    static QList<DesignerMainWnd*> mainWnd_list;
private slots:
    void on_tabWidget_tabCloseRequested(int index);
    void on_actionFileSaveAs_triggered();
};

#endif // DESIGNERMAINWND_H
