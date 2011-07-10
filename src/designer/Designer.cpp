#include <QtGui/QApplication>
#include <QDesktopServices>
#include <QSplashScreen>
#include <QTextCodec>
#include "DesignerMainWnd.h"

int main(int argc, char *argv[])
{
    QApplication designer(argc, argv);
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
    DesignerMainWnd::globalCreateNewMainWnd();

    return designer.exec();
}
