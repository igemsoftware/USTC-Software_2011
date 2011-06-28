#ifndef ASSEMBLYCREATEANDDRAG_H
#define ASSEMBLYCREATEANDDRAG_H

#include <QMessageBox>

#include <QToolButton>
#include <QDrag>
#include <QMimeData>


class AssemblyCreateAndDrag : public QToolButton
{
    Q_OBJECT
public:
    explicit AssemblyCreateAndDrag( QString setType , QString setName , QWidget *parent = 0);

signals:

public slots:
    void createAndDrag();

private:
    QString name;
    QString type;
};

#endif // ASSEMBLYCREATEANDDRAG_H
