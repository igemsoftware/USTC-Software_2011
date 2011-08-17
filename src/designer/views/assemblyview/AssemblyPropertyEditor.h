#ifndef ASSEMBLYPROPERTYEDITOR_H
#define ASSEMBLYPROPERTYEDITOR_H

#include <QDialog>
#include <QLayout>
#include <QFormLayout>
#include "AssemblyLib.h"

class AssemblyPropertyEditor : public QDialog
{
    Q_OBJECT
public:
    explicit AssemblyPropertyEditor( QString newType , QScriptValueList & newScriptValueList , QScriptEngine * newEngine , QWidget *parent = 0);

    static bool setCombo( QString name , QList<QScriptValue> * combo );
signals:

public slots:
    void setIndex(int newIndex);
    void accept();
private:


    enum PropertyType
    {
        TypeBool,
        TypeCombo,
        TypeString,
        TypeNumber
    };
    struct PropertySpecifier
    {
        QString name;
        QString label;
        PropertyType type;
        QString combo;
        PropertySpecifier(
            QString tname,
            QString tlabel,
            PropertyType ttype,
            QString tcombo = "")
            :
            name(tname),
            label(tlabel),
            type(ttype),
            combo(tcombo){}
    };
    struct ScriptTypeSpecifier
    {
        QString type;
        bool enableAdd;
        QList<PropertySpecifier> properties;
    };
    static QMap<QString,QList<QScriptValue>*> comboMap;
    static QMap<QString,ScriptTypeSpecifier> typeMap;
    static void initializeOnce();

    int index;
    QString type;
    QScriptValueList & valueList;
    QFormLayout * form;
    QScriptEngine * engine;
};

#endif // ASSEMBLYPROPERTYEDITOR_H
