#ifndef ASSEMBLYDBEDITOR_H
#define ASSEMBLYDBEDITOR_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

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
private:
    Ui::AssemblyDBEditor *ui;

    QSqlDatabase db;
    QSqlTableModel *agentModel,*ruleModel;


};

#endif // ASSEMBLYDBEDITOR_H
