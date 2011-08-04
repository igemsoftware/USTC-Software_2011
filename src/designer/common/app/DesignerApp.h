#include <QtSingleApplication>

#ifndef DESIGNERAPP_H
#define DESIGNERAPP_H

class DesignerApp : public QtSingleApplication
{
    Q_OBJECT
public:
    explicit DesignerApp(int & argc, char ** argv, bool GUIenabled = true);

    bool initApplication();
    void sendCommandLineAsMessage();

    void updateConfiguration();

};

#endif // DESIGNERAPP_H
