#ifndef DESIGNERMODELCOMPONENT_H
#define DESIGNERMODELCOMPONENT_H

#include "DesignerModelItf.h"

class DesignerModelComponent : public QObject,
                                public DesignerModelItf
{
    Q_OBJECT
    Q_INTERFACES(DesignerModelItf)

    //constructor
protected:
    //! Constructor for initialization, should be called by children class constructors.
    explicit DesignerModelComponent(DesignerDocComponent *currentDoc);
public:
    //! Call this method to create a model object
    //! \param modelName The name of the model, which should be the class name
    //! \param currentDoc Set the document object at the same time. Useful when loading the model from a file.
    static DesignerModelComponent* createModel(QString modelName, DesignerDocComponent *currentDoc = 0);

    //internal data
protected:
    //! The local data store.
    QScriptEngine modelEngine;
public:
    //! Call this method to retrieve the local data store.
    //! Notice that if you modify the data directly from here,
    //! You'll need to set this model to Modified state manually.
    QScriptEngine* getEngine() {return &modelEngine;}
    QScriptValue  getModel() {return getEngine()->globalObject().property("model");}

    //model hierarchy
public:
    //! When this is a submodel of another model, parentModel will be the pointer
    //! to that model.
    DesignerModelComponent* parentModel;

    //! The list of submodels of this model.
    QList<DesignerModelComponent*> subModels;

    //serialization support
private:
    //! \internal Pointer to the document object.
    DesignerDocComponent *currentDoc;
public:
    //! Retrieve the pointer to the document object.
    //! NULL is the model is never saved yet.
    DesignerDocComponent *getCurrentDoc() { return currentDoc; }
    void setCurrentDoc(DesignerDocComponent* newDoc) {currentDoc = newDoc;}

    // modified flag
public:
    //! Retrieve the modified flag associated with this document.
    bool isModified() const {return modified;}
    //! Update the modified flag associated with this document.
    void setModified(bool newValue = true) {modified = newValue;}
protected:
    bool modified;

signals:
    void dataUpdated();
    void storageUpdated();

public:
    enum UpdateFlags
    {
        updateByData = 1,
        updateByStorage = 2
    };
public slots:
    void requestUpdate(unsigned int flags)
    {
        if(flags&updateByStorage)
        {
            emit storageUpdated();
        }
        if(flags&updateByData)
        {
            emit dataUpdated();
        }
    }

public:
    //! Execute a piece of script.
    //! Useful for extension support.
    QScriptValue evaluate(QString sourceCode)
    {
        return modelEngine.evaluate(sourceCode, tr("lachesis_script.tmp"));
    }

public:
    struct ModelItfRegistryItem
    {
        const QMetaObject* metaObject;

        ModelItfRegistryItem(const QMetaObject* m = 0)
            : metaObject(m){}
     };

    //! The archive for model dynamic loading
    typedef ItemRegistry<QString, ModelItfRegistryItem> ModelItfRegistry;

public:
    //! Initialization(dynamic loading).
    static void initializeIfNotYet();


};


#endif // DESIGNERMODELCOMPONENT_H
