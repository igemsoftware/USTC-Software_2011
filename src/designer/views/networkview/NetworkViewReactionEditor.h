#ifndef NETWORKVIEWREACTIONEDITOR_H
#define NETWORKVIEWREACTIONEDITOR_H

#include <QDialog>
#include <QScriptValue>

namespace Ui {
    class NetworkViewReactionEditor;
}

class NetworkViewReactionEditor : public QDialog
{
    Q_OBJECT

public:
    QScriptValue property;
    QSet<QString> *idSpace;
    explicit NetworkViewReactionEditor(QScriptValue &value,QSet<QString> *idSpace,QWidget *parent = 0);
    ~NetworkViewReactionEditor();

private:
    Ui::NetworkViewReactionEditor *ui;

public slots:
    void accept();
};

#endif // NETWORKVIEWREACTIONEDITOR_H
