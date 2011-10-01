#ifndef ASSEMBLYDBEDITOR_H
#define ASSEMBLYDBEDITOR_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>


namespace Ui {
    class AssemblyDBEditor;
}

class AssemblyDBEditor : public QDialog
{
    Q_OBJECT

public:
    explicit AssemblyDBEditor(QWidget *parent = 0);
    ~AssemblyDBEditor();

public slots:
    void refresh();
    void addSet();
    void removeSet();
    void selectTable( QString table );

    void addRow();
    void removeRow();
private:
    Ui::AssemblyDBEditor *ui;
    QStringList builtinTables;
    QSqlDatabase db;
    QSqlTableModel *tableModel;


};

#endif // ASSEMBLYDBEDITOR_H
