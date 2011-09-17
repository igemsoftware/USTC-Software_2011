#ifndef DESIGNERVIEWMGR_H
#define DESIGNERVIEWMGR_H

#include <QtCore>
#include "interfaces/DesignerViewItf.h"
#include "common/utils/itemregistry/ItemRegistry.h"

class DesignerViewComponent;

class DesignerViewMgr
{
public:
    struct ViewItfRegistryItem
    {
        const QMetaObject*  metaObject;
        QString             viewTitle;
        QString             defaultModelName;

        ViewItfRegistryItem(const QMetaObject* m = 0,QString v = "Invalid", QString d = "")
            : metaObject(m), viewTitle(v), defaultModelName(d) {}
     };

    //! The archive for view dynamic loading
    typedef ItemRegistry<QString, ViewItfRegistryItem> ViewItfRegistry;
public:
    //! Initialization(dynamic loading).
    static void initializeIfNotYet();

public:

    //! Create a view.
    static DesignerViewComponent* createView(QString viewName, DesignerMainWnd* mainWnd, DesignerModelComponent* model);
    //! Retrieve the attributes of a view
    static QString getViewTitleByName(QString viewName);
    //! Retrieve the attributes of a view
    static QString getViewDefaultModelByName(QString viewName);
    //! Retrieve the attributes of a view
    static QMetaObject getViewMetaObjectByName(QString name);

};

#endif // DESIGNERVIEWMGR_H
