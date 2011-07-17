#ifndef DESIGNERMODELITF_H
#define DESIGNERMODELITF_H

#include <QObject>
#include <QScriptEngine>

class DesignerDocItf;

class DesignerModelItf : public QObject
{
    Q_OBJECT

    //constructor
protected:
    //! Constructor for initialization, should be called by children class constructors.
    explicit DesignerModelItf(DesignerDocItf *currentDoc);
public:
    //! Call this method to create a model object
    //! \param modelName The name of the model, which should be the class name
    //! \param currentDoc Set the document object at the same time. Useful when loading the model from a file.
    static DesignerModelItf* createModel(QString modelName, DesignerDocItf *currentDoc = 0);

    //internal data
protected:
    //! The local data store.
    QScriptEngine modelEngine;
public:
    //! Call this method to retrieve the local data store.
    //! Notice that if you modify the data directly from here,
    //! You'll need to set this model to Modified state manually.
    QScriptEngine* getEngine() {return &modelEngine;}

    //model hierarchy
public:
    //! When this is a submodel of another model, parentModel will be the pointer
    //! to that model.
    DesignerModelItf* parentModel;

    //! The list of submodels of this model.
    QList<DesignerModelItf*> subModels;

    //display support
public:
    virtual QStringList getSupportedViewList() const = 0;


    //serialization support
private:
    DesignerDocItf *currentDoc;
public:
    //! Retrieve the pointer to the document object.
    //! NULL is the model is never saved yet.
    DesignerDocItf *getCurrentDoc() { return currentDoc; }


    //manipulation methods (overridable)
public:
    typedef size_t modelObjectIndex;

    //! Implement dependent
    virtual modelObjectIndex createModelObject(modelObjectIndex parent = 0, void* data = 0) = 0;
    //! Implement dependent
    virtual void removeModelObject(modelObjectIndex index) = 0;
    //! Implement dependent
    virtual void setModelObjectProperty(modelObjectIndex index, QString propertyName, QString value) = 0;
    //! Implement dependent
    virtual QString getModelObjectProperty(modelObjectIndex index, QString propertyName) = 0;


public:
    //! Execute a piece of script.
    //! Useful for extension support.
    QScriptValue evaluate(QString sourceCode)
    {
        return modelEngine.evaluate(sourceCode, tr("lachesis_script.tmp"));
    }

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
