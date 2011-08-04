#include <QDesktopServices>
#include <QSplashScreen>
#include <QTextCodec>

#include "common/app/DesignerApp.h"
#include "common/mainwnd/DesignerMainWnd.h"

#include "interfaces/DesignerInterface.h"


DesignerApp::DesignerApp(int & argc, char ** argv, bool GUIenabled) :
    QtSingleApplication(argc, argv, GUIenabled)
{

}

bool DesignerApp::initApplication()
{
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    QPixmap pixmap(":/designer/splash.png");
    QSplashScreen *splash = new QSplashScreen(pixmap);
    splash->show();
    splash->showMessage(tr("Loading..."));

    processEvents();

    updateConfiguration();
    DesignerViewItf::initializeIfNotYet();
    DesignerDocItf::initializeIfNotYet();
    DesignerModelItf::initializeIfNotYet();
    DesignerExtensionItf::initializeIfNotYet();


    DesignerMainWnd* mainWnd = DesignerMainWnd::globalCreateNewMainWnd();
    setActivationWindow(mainWnd);
    QObject::connect(this, SIGNAL(messageReceived(const QString&)), mainWnd, SLOT(instanceMessageReceived(const QString&)));
    splash->setWindowFlags(Qt::WindowStaysOnTopHint);
    splash->setParent(mainWnd);
    splash->show();

    QTimer::singleShot(1500, splash, SLOT(close()));
    while(splash->isVisible())
    {
        processEvents();
    }

    return true;
}

void DesignerApp::updateConfiguration()
{
    QSettings settings(QDesktopServices::storageLocation(QDesktopServices::HomeLocation)
                                                         + "/.lachesis/lachesis.conf", QSettings::IniFormat);
    settings.beginGroup("Designer");
    settings.setValue("AppPath", QtSingleApplication::applicationFilePath());
    settings.endGroup();
    settings.sync();
}

void DesignerApp::sendCommandLineAsMessage()
{
    //! \todo add more code here.
    sendMessage("/new");
}
