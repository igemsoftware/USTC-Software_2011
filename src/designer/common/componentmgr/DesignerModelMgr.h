#ifndef DESIGNERMODELMGR_H
#define DESIGNERMODELMGR_H

#include <QtCore>
#include "common/utils/itemregistry/ItemRegistry.h"

class DesignerDocComponent;
class DesignerModelComponent;

class DesignerModelMgr
{
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
public:
    //! Call this method to create a model object
    //! \param modelName The name of the model, which should be the class name
    //! \param currentDoc Set the document object at the same time. Useful when loading the model from a file.
    static DesignerModelComponent* createModel(QString modelName, DesignerDocComponent *currentDoc = 0);

};

#endif // DESIGNERMODELMGR_H
