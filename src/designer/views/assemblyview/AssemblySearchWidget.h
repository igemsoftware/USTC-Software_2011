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
#include <QSqlDatabase>
#include <QSqlQuery>

class AssemblySearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AssemblySearchWidget( QScriptEngine * newEngine , QWidget *parent = 0);

signals:

public slots:
    void inputChanges(QString);
    void startDrag( QModelIndex index );
    void reload();
private:
    QSqlDatabase db;
    QSqlQuery * query;
    QScriptEngine * engine;
    QTableWidget * tableWidget;
    QLineEdit * lineEdit;
    QComboBox * typeCombo , * compartmentCombo;
};

#endif // ASSEMBLYSEARCHWIDGET_H
