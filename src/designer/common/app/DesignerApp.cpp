#include <QDesktopServices>
#include <QSplashScreen>
#include <QTextCodec>

#include "common/app/DesignerApp.h"
#include "common/mainwnd/DesignerMainWnd.h"

#include "common/componentmgr/DesignerDocMgr.h"
#include "common/componentmgr/DesignerViewMgr.h"
#include "common/componentmgr/DesignerModelMgr.h"
#include "common/componentmgr/DesignerExtensionMgr.h"

#include "interfaces/DesignerInterface.h"


DesignerApp::DesignerApp(int & argc, char ** argv, bool GUIenabled) :
    QtSingleApplication(argc, argv, GUIenabled),
    settings(QDesktopServices::storageLocation(QDesktopServices::HomeLocation) + "/.lachesis/lachesis.conf", QSettings::IniFormat)
{

}

bool DesignerApp::initApplication(QString cmdLine)
{
    QLocale::setDefault(QLocale(QLocale::English));
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    QPixmap pixmap(":/designer/splash.png");
    QSplashScreen *splash = new QSplashScreen(pixmap);
    splash->show();
    splash->showMessage(tr("Loading..."));

    processEvents();

    writeConfigValue("", "apppath", QtSingleApplication::applicationFilePath());

    dbIgame = QSqlDatabase::addDatabase("QMYSQL","igame");
    dbIgame.setDatabaseName("MoDeL");
    dbIgame.setHostName("localhost");
    dbIgame.setUserName("root");
    dbIgame.setPassword("lovewin");
    dbIgame.open();

    DesignerViewMgr::initializeIfNotYet();
    DesignerDocMgr::initializeIfNotYet();
    DesignerModelMgr::initializeIfNotYet();

    DesignerExtensionMgr::initializeIfNotYet();

    DesignerMainWnd* mainWnd = DesignerMainWnd::globalCreateNewMainWnd();
    setActivationWindow(mainWnd);
    QObject::connect(this, SIGNAL(messageReceived(const QString&)), mainWnd, SLOT(instanceMessageReceived(const QString&)));
    splash->setWindowFlags(Qt::WindowStaysOnTopHint);
    splash->setParent(mainWnd);
    splash->show();

    QTimer::singleShot(1500, splash, SLOT(close()));

    if(cmdLine!="/new")
        mainWnd->instanceMessageReceived(cmdLine);

    while(splash->isVisible())
    {
        processEvents();
    }

    return true;
}

QVariant DesignerApp::readConfigValue(QString group, QString name, QVariant defaultValue)
{
    QString fullGroupName = "designer";
    if(group.length())
        fullGroupName+=".";
    fullGroupName+=group;

    QVariant retValue;

    settings.beginGroup(fullGroupName);
    retValue = settings.value(name);
    settings.endGroup();

    if(!retValue.isValid())
    {
        writeConfigValue(group, name, defaultValue);
        return defaultValue;
    }

    return retValue;
}

void DesignerApp::writeConfigValue(QString group, QString name, QVariant value)
{
    QString fullGroupName = "designer";
    if(group.length())
        fullGroupName+=".";
    fullGroupName+=group;

    settings.beginGroup(fullGroupName);
    settings.setValue(name, value);
    settings.endGroup();
}
