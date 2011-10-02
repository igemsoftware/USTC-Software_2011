#include <QtSingleApplication>
#include <QSqlDatabase>
#include <QSettings>

#ifndef DESIGNERAPP_H
#define DESIGNERAPP_H

class DesignerApp : public QtSingleApplication
{
    Q_OBJECT
public:
    explicit DesignerApp(int & argc, char ** argv, bool GUIenabled = true);

    bool initApplication(QString cmdLine);

    QVariant readConfigValue(QString group, QString name, QVariant defaultValue = QVariant());
    void writeConfigValue(QString group, QString name, QVariant value);

protected:
    QSettings settings;
    QSqlDatabase dbIgame;
public:
    static DesignerApp* instance(){ return (DesignerApp*)QtSingleApplication::instance();}
};

#endif // DESIGNERAPP_H
