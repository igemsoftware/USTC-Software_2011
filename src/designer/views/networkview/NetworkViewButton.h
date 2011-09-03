#ifndef NETWORKVIEWBUTTON_H
#define NETWORKVIEWBUTTON_H

#include <QMessageBox>

#include <QPushButton>
#include <QDrag>
#include <QMimeData>
#include <QScriptEngine>

class NetworkViewButton : public QPushButton
{
    Q_OBJECT
public:
    explicit NetworkViewButton( QString newType , QScriptValue newScriptValue , QPixmap newIcon = QPixmap( tr(":/designer/oops.png") ) , QWidget *parent = 0);

signals:

public slots:
    void createAndDrag();

private:
    QScriptValue scriptValue;
    QString type;
    QPixmap icon;
};

#endif // NETWORKVIEWBUTTON_H
