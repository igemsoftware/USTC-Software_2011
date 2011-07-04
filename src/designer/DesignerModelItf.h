#ifndef DESIGNERMODELITF_H
#define DESIGNERMODELITF_H

#include <QObject>

class DesignerModelItf : public QObject
{
    Q_OBJECT
public:
    explicit DesignerModelItf(QObject *parent = 0);

    static DesignerModelItf* createModel(QString modelName);

public:
    typedef size_t modelObjectIndex;

    virtual modelObjectIndex createModelObject(modelObjectIndex parent = 0, void* data = 0) = 0;
    virtual void removeModelObject(modelObjectIndex index) = 0;
    virtual void setModelObjectProperty(modelObjectIndex index, QString propertyName, QString value) = 0;
    virtual QString getModelObjectProperty(modelObjectIndex index, QString propertyName) = 0;



signals:

public slots:

};

class DesignerModelFormatProxyItf : public QObject
{
    Q_OBJECT
private:
    DesignerModelItf* modelItf;
public:
    DesignerModelFormatProxyItf(DesignerModelItf* itf) : modelItf(itf){}
    DesignerModelItf* getModel() {return modelItf;}
public:
    typedef size_t modelObjectIndex;

    virtual modelObjectIndex createModelObject(modelObjectIndex parent = 0, void* data = 0) = 0;
    virtual void setModelObjectProperty(modelObjectIndex index, QString propertyName, QString value) = 0;
    virtual QString getModelObjectProperty(modelObjectIndex index, QString propertyName) = 0;
    virtual void removeModelObject(modelObjectIndex index) = 0;
};

#endif // DESIGNERMODELITF_H
