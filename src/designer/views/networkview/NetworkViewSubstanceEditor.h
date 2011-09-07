#ifndef NETWORKVIEWSUBSTANCEEDITOR_H
#define NETWORKVIEWSUBSTANCEEDITOR_H

#include <QDialog>
#include <QScriptValue>

namespace Ui {
    class NetworkViewSubstanceEditor;
}

class NetworkViewSubstanceEditor : public QDialog
{
    Q_OBJECT

public:
    QScriptValue property;
    QSet<QString> *idSpace;
    explicit NetworkViewSubstanceEditor(QScriptValue &value,QSet<QString> *idSpace,QWidget *parent = 0);
    ~NetworkViewSubstanceEditor();

private:
    Ui::NetworkViewSubstanceEditor *ui;

public slots:
    void accept();
};

#endif // NETWORKVIEWSUBSTANCEEDITOR_H
