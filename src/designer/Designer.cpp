#include "common/app/DesignerApp.h"
#include "DesignerMainWnd.h"


int main(int argc, char *argv[])
{
    DesignerApp designer(argc, argv);

    if(designer.isRunning())
    {
        designer.sendCommandLineAsMessage();
        return 0;
    }

    if(!designer.initApplication())
        return -1;

    DesignerMainWnd* mainWnd = DesignerMainWnd::globalCreateNewMainWnd();
    designer.setActivationWindow(mainWnd);

    QObject::connect(&designer, SIGNAL(messageReceived(const QString&)), mainWnd, SLOT(instanceMessageReceived(const QString&)));

    return designer.exec();
}
