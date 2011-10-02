#include "common/app/DesignerApp.h"
int main(int argc, char *argv[])
{
    DesignerApp designer(argc, argv);
    QString cmdLine;
    if(argc<=1)
    {
        cmdLine = "/new";
    }
    else
    {
        QString filePath = QString(argv[1]);
        if(!filePath.startsWith("http://"))
            cmdLine = "/open ";
        else
            cmdLine = "/openurl ";
        cmdLine += filePath;
    }

    if(designer.isRunning())
    {
        if(designer.sendMessage(cmdLine));
            return 0;
    }

    if(!designer.initApplication(cmdLine))
        return -1;

    return designer.exec();
}
