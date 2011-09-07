#ifndef NETWORKVIEWCONTAINEREDITOR_H
#define NETWORKVIEWCONTAINEREDITOR_H

#include <QDialog>
#include <QScriptValue>

namespace Ui {
    class NetworkViewContainerEditor;
}

class NetworkViewContainerEditor : public QDialog
{
    Q_OBJECT

public:
    QScriptValue property;
    QSet<QString> *idSpace;
    explicit NetworkViewContainerEditor(QScriptValue &value,QSet<QString> *idSpace,QWidget *parent = 0);
    ~NetworkViewContainerEditor();

private:
    Ui::NetworkViewContainerEditor *ui;

public slots:
    void accept();
};

#endif // NETWORKVIEWCONTAINEREDITOR_H
