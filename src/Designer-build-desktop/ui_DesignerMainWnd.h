/********************************************************************************
** Form generated from reading UI file 'DesignerMainWnd.ui'
**
** Created: Mon Jun 27 20:59:40 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DESIGNERMAINWND_H
#define UI_DESIGNERMAINWND_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DesignerMainWnd
{
public:
    QAction *actionNew_Window;
    QAction *actionE_xit;
    QAction *action;
    QAction *action_New_File;
    QAction *action_Save;
    QAction *actionSave_as;
    QAction *action_Undo;
    QAction *action_Cut;
    QAction *actionC_opy;
    QAction *action_Paste;
    QAction *action_About_Lachesis_Designer;
    QAction *actionAbout_Qt;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Edit;
    QMenu *menu_View;
    QMenu *menu_Help;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;

    void setupUi(QMainWindow *DesignerMainWnd)
    {
        if (DesignerMainWnd->objectName().isEmpty())
            DesignerMainWnd->setObjectName(QString::fromUtf8("DesignerMainWnd"));
        DesignerMainWnd->resize(917, 645);
        DesignerMainWnd->setStyleSheet(QString::fromUtf8("background-color: rgb(32, 65, 98);"));
        actionNew_Window = new QAction(DesignerMainWnd);
        actionNew_Window->setObjectName(QString::fromUtf8("actionNew_Window"));
        actionE_xit = new QAction(DesignerMainWnd);
        actionE_xit->setObjectName(QString::fromUtf8("actionE_xit"));
        action = new QAction(DesignerMainWnd);
        action->setObjectName(QString::fromUtf8("action"));
        action_New_File = new QAction(DesignerMainWnd);
        action_New_File->setObjectName(QString::fromUtf8("action_New_File"));
        action_Save = new QAction(DesignerMainWnd);
        action_Save->setObjectName(QString::fromUtf8("action_Save"));
        actionSave_as = new QAction(DesignerMainWnd);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        action_Undo = new QAction(DesignerMainWnd);
        action_Undo->setObjectName(QString::fromUtf8("action_Undo"));
        action_Cut = new QAction(DesignerMainWnd);
        action_Cut->setObjectName(QString::fromUtf8("action_Cut"));
        actionC_opy = new QAction(DesignerMainWnd);
        actionC_opy->setObjectName(QString::fromUtf8("actionC_opy"));
        action_Paste = new QAction(DesignerMainWnd);
        action_Paste->setObjectName(QString::fromUtf8("action_Paste"));
        action_About_Lachesis_Designer = new QAction(DesignerMainWnd);
        action_About_Lachesis_Designer->setObjectName(QString::fromUtf8("action_About_Lachesis_Designer"));
        actionAbout_Qt = new QAction(DesignerMainWnd);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        centralWidget = new QWidget(DesignerMainWnd);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        DesignerMainWnd->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DesignerMainWnd);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 917, 23));
        menuBar->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(255, 255, 255, 255), stop:1 rgba(220, 235, 246, 255));"));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_Edit = new QMenu(menuBar);
        menu_Edit->setObjectName(QString::fromUtf8("menu_Edit"));
        menu_View = new QMenu(menuBar);
        menu_View->setObjectName(QString::fromUtf8("menu_View"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        DesignerMainWnd->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DesignerMainWnd);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(255, 255, 255, 255), stop:1 rgba(220, 235, 246, 255));"));
        DesignerMainWnd->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DesignerMainWnd);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setStyleSheet(QString::fromUtf8("background-color: rgb(172, 172, 172);"));
        DesignerMainWnd->setStatusBar(statusBar);
        dockWidget = new QDockWidget(DesignerMainWnd);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(172, 172, 172);"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        dockWidget->setWidget(dockWidgetContents);
        DesignerMainWnd->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Edit->menuAction());
        menuBar->addAction(menu_View->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_New_File);
        menu_File->addSeparator();
        menu_File->addAction(action_Save);
        menu_File->addAction(actionSave_as);
        menu_File->addSeparator();
        menu_File->addAction(actionE_xit);
        menu_Edit->addAction(action_Undo);
        menu_Edit->addSeparator();
        menu_Edit->addAction(action_Cut);
        menu_Edit->addAction(actionC_opy);
        menu_Edit->addAction(action_Paste);
        menu_Help->addAction(actionAbout_Qt);
        menu_Help->addAction(action_About_Lachesis_Designer);

        retranslateUi(DesignerMainWnd);

        QMetaObject::connectSlotsByName(DesignerMainWnd);
    } // setupUi

    void retranslateUi(QMainWindow *DesignerMainWnd)
    {
        DesignerMainWnd->setWindowTitle(QApplication::translate("DesignerMainWnd", "DesignerMainWnd", 0, QApplication::UnicodeUTF8));
        actionNew_Window->setText(QApplication::translate("DesignerMainWnd", "New Window", 0, QApplication::UnicodeUTF8));
        actionE_xit->setText(QApplication::translate("DesignerMainWnd", "E&xit", 0, QApplication::UnicodeUTF8));
        action->setText(QApplication::translate("DesignerMainWnd", "-", 0, QApplication::UnicodeUTF8));
        action_New_File->setText(QApplication::translate("DesignerMainWnd", "&New File...", 0, QApplication::UnicodeUTF8));
        action_Save->setText(QApplication::translate("DesignerMainWnd", "&Save", 0, QApplication::UnicodeUTF8));
        action_Save->setShortcut(QApplication::translate("DesignerMainWnd", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionSave_as->setText(QApplication::translate("DesignerMainWnd", "Save &as...", 0, QApplication::UnicodeUTF8));
        action_Undo->setText(QApplication::translate("DesignerMainWnd", "&Undo", 0, QApplication::UnicodeUTF8));
        action_Cut->setText(QApplication::translate("DesignerMainWnd", "&Cut", 0, QApplication::UnicodeUTF8));
        actionC_opy->setText(QApplication::translate("DesignerMainWnd", "C&opy", 0, QApplication::UnicodeUTF8));
        action_Paste->setText(QApplication::translate("DesignerMainWnd", "&Paste", 0, QApplication::UnicodeUTF8));
        action_About_Lachesis_Designer->setText(QApplication::translate("DesignerMainWnd", "&About Lachesis Designer...", 0, QApplication::UnicodeUTF8));
        actionAbout_Qt->setText(QApplication::translate("DesignerMainWnd", "About Qt...", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("DesignerMainWnd", "&File", 0, QApplication::UnicodeUTF8));
        menu_Edit->setTitle(QApplication::translate("DesignerMainWnd", "&Edit", 0, QApplication::UnicodeUTF8));
        menu_View->setTitle(QApplication::translate("DesignerMainWnd", "&View", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("DesignerMainWnd", "&Help", 0, QApplication::UnicodeUTF8));
        dockWidget->setWindowTitle(QApplication::translate("DesignerMainWnd", "Properties", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DesignerMainWnd: public Ui_DesignerMainWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESIGNERMAINWND_H
