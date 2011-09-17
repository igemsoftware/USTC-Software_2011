#ifndef NETWORKVIEWREACTIONEDITOR_H
#define NETWORKVIEWREACTIONEDITOR_H

#include <QDialog>
#include <QScriptValue>
#include <QtMmlWidget>

namespace Ui {
    class NetworkViewReactionEditor;
}

class NetworkViewReactionEditor : public QDialog
{
    Q_OBJECT

public:
    QtMmlWidget *mml;
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
