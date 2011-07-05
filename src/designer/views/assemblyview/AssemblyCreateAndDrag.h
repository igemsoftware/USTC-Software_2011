#ifndef ASSEMBLYCREATEANDDRAG_H
#define ASSEMBLYCREATEANDDRAG_H

#include <QMessageBox>

#include <QToolButton>
#include <QDrag>
#include <QMimeData>
#include <QScriptEngine>

class AssemblyCreateAndDrag : public QToolButton
{
    Q_OBJECT
public:
    explicit AssemblyCreateAndDrag( QString newType , QScriptValue newScriptValue , QPixmap newIcon = QPixmap( tr(":/designer/oops.png") ) , QWidget *parent = 0);

signals:

public slots:
    void createAndDrag();

private:
    QScriptValue scriptValue;
    QString type;
    QPixmap icon;
};

#endif // ASSEMBLYCREATEANDDRAG_H
