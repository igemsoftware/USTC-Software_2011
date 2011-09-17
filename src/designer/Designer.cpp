#include "common/app/DesignerApp.h"

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

    return designer.exec();
}
