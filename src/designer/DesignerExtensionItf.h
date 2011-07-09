#ifndef DESIGNEREXTENSIONITF_H
#define DESIGNEREXTENSIONITF_H

#include <QObject>

class DesignerExtensionItf : public QObject
{
    Q_OBJECT
public:
    explicit DesignerExtensionItf(QObject *parent = 0);

signals:

public slots:

};

#endif // DESIGNEREXTENSIONITF_H
