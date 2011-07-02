#ifndef DESIGNERMODELITF_H
#define DESIGNERMODELITF_H

#include <QObject>

class DesignerModelItf : public QObject
{
    Q_OBJECT
public:
    explicit DesignerModelItf(QObject *parent = 0);

    static DesignerModelItf* createModel(QString& modelName);

signals:

public slots:

};

#endif // DESIGNERMODELITF_H
