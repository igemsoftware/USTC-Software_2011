#ifndef DESIGNERDOCITF_H
#define DESIGNERDOCITF_H

#include <QObject>

class DesignerDocItf : public QObject
{
    Q_OBJECT
public:
    explicit DesignerDocItf(QObject *parent = 0);

signals:

public slots:

};

#endif // DESIGNERDOCITF_H
