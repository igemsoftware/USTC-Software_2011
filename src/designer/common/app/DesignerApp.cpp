#include <QDesktopServices>
#include <QSplashScreen>
#include <QTextCodec>

#include "common/app/DesignerApp.h"
#include "interfaces/DesignerInterface.h"


DesignerApp::DesignerApp(int & argc, char ** argv, bool GUIenabled) :
    QtSingleApplication(argc, argv, GUIenabled)
{

}

bool DesignerApp::initApplication()
{
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    QPixmap pixmap(":/designer/splash.png");
    QSplashScreen *splash = new QSplashScreen(pixmap, Qt::WindowStaysOnTopHint);
    splash->show();
    splash->showMessage(tr("Loading..."));

    processEvents();

    updateConfiguration();
    DesignerViewItf::initializeIfNotYet();
    DesignerDocItf::initializeIfNotYet();

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
