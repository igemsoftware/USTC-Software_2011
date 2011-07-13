#include <QtSingleApplication>
#include <QtGui/QApplication>
#include <QDesktopServices>
#include <QSplashScreen>
#include <QTextCodec>
#include "DesignerMainWnd.h"

int main(int argc, char *argv[])
{
    QtSingleApplication designer(argc, argv);
    if(designer.isRunning())
    {
        designer.sendMessage("/new");
        return 0;
    }

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    QPixmap pixmap(":/designer/splash.png");
    QSplashScreen *splash = new QSplashScreen(pixmap, Qt::WindowStaysOnTopHint);
    splash->show();
    splash->showMessage("Loading...");
    designer.processEvents();
    QTimer::singleShot(1500, splash, SLOT(close()));


    while(splash->isVisible())
    {
        designer.processEvents();
    }


    DesignerMainWnd* mainWnd = DesignerMainWnd::globalCreateNewMainWnd();
    designer.setActivationWindow(mainWnd);

    QObject::connect(&designer, SIGNAL(messageReceived(const QString&)), mainWnd, SLOT(instanceMessageReceived(const QString&)));

    return designer.exec();
}
