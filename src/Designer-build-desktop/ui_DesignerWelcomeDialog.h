/********************************************************************************
** Form generated from reading UI file 'DesignerWelcomeDialog.ui'
**
** Created: Mon Jun 27 20:59:40 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DESIGNERWELCOMEDIALOG_H
#define UI_DESIGNERWELCOMEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCommandLinkButton>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WelcomeDialog
{
public:
    QFrame *frame;
    QCommandLinkButton *buttonQuit;
    QGroupBox *groupBox_2;
    QCommandLinkButton *buttonOpenFile;
    QLabel *label;
    QGroupBox *groupBox;
    QCommandLinkButton *buttonCreateNetworkFile;
    QCommandLinkButton *buttonCreateBehaviorFile;
    QCommandLinkButton *buttonCreateAssemblyFile;

    void setupUi(QWidget *WelcomeDialog)
    {
        if (WelcomeDialog->objectName().isEmpty())
            WelcomeDialog->setObjectName(QString::fromUtf8("WelcomeDialog"));
        WelcomeDialog->resize(554, 435);
        WelcomeDialog->setAutoFillBackground(false);
        WelcomeDialog->setStyleSheet(QString::fromUtf8("background-color: rgb(244, 249, 255);"));
        frame = new QFrame(WelcomeDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 561, 441));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(5);
        buttonQuit = new QCommandLinkButton(frame);
        buttonQuit->setObjectName(QString::fromUtf8("buttonQuit"));
        buttonQuit->setGeometry(QRect(417, 370, 91, 41));
        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(280, 70, 231, 281));
        buttonOpenFile = new QCommandLinkButton(groupBox_2);
        buttonOpenFile->setObjectName(QString::fromUtf8("buttonOpenFile"));
        buttonOpenFile->setGeometry(QRect(30, 50, 172, 41));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(17, 20, 241, 16));
        label->setStyleSheet(QString::fromUtf8("font: 14pt;"));
        label->setTextFormat(Qt::PlainText);
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(17, 70, 221, 281));
        buttonCreateNetworkFile = new QCommandLinkButton(groupBox);
        buttonCreateNetworkFile->setObjectName(QString::fromUtf8("buttonCreateNetworkFile"));
        buttonCreateNetworkFile->setGeometry(QRect(20, 130, 172, 41));
        buttonCreateBehaviorFile = new QCommandLinkButton(groupBox);
        buttonCreateBehaviorFile->setObjectName(QString::fromUtf8("buttonCreateBehaviorFile"));
        buttonCreateBehaviorFile->setGeometry(QRect(20, 210, 172, 41));
        buttonCreateAssemblyFile = new QCommandLinkButton(groupBox);
        buttonCreateAssemblyFile->setObjectName(QString::fromUtf8("buttonCreateAssemblyFile"));
        buttonCreateAssemblyFile->setGeometry(QRect(20, 50, 172, 41));

        retranslateUi(WelcomeDialog);

        QMetaObject::connectSlotsByName(WelcomeDialog);
    } // setupUi

    void retranslateUi(QWidget *WelcomeDialog)
    {
        WelcomeDialog->setWindowTitle(QApplication::translate("WelcomeDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        buttonQuit->setText(QApplication::translate("WelcomeDialog", "Exit", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("WelcomeDialog", "Open existing file...", 0, QApplication::UnicodeUTF8));
        buttonOpenFile->setText(QApplication::translate("WelcomeDialog", "From file...", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("WelcomeDialog", "Lachesis Designer", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("WelcomeDialog", "Create new file...", 0, QApplication::UnicodeUTF8));
        buttonCreateNetworkFile->setText(QApplication::translate("WelcomeDialog", "Network file", 0, QApplication::UnicodeUTF8));
        buttonCreateBehaviorFile->setText(QApplication::translate("WelcomeDialog", "Behavior file", 0, QApplication::UnicodeUTF8));
        buttonCreateAssemblyFile->setText(QApplication::translate("WelcomeDialog", "Parts-assembly file", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WelcomeDialog: public Ui_WelcomeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESIGNERWELCOMEDIALOG_H
