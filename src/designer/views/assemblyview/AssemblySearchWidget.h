#ifndef ASSEMBLYSEARCHWIDGET_H
#define ASSEMBLYSEARCHWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QLayout>
#include <QScriptEngine>
#include <QMouseEvent>
#include <QScriptValueIterator>

class AssemblySearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AssemblySearchWidget( QScriptEngine * newEngine , QWidget *parent = 0);

signals:

public slots:
    void inputChanges(QString);
    void startDrag( QModelIndex index );

private:
    QScriptEngine * engine;
    QTableWidget * tableWidget;
    QLineEdit * lineEdit;
    QComboBox * comboBox;

    QMap<QString,int> propertyColumn;

    QScriptValueList partList;


    QScriptValueList query( QString type , QString name );
};

#endif // ASSEMBLYSEARCHWIDGET_H
