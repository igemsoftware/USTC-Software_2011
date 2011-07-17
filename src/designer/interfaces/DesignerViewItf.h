//! \file DesignerViewItf.h
//! Lachesis Designer View Common Interface

#ifndef DESIGNERVIEWITF_H
#define DESIGNERVIEWITF_H

#include <QtCore>
#include <QtGui>
#include "common/utils/itemregistry/ItemRegistry.h"

class DesignerModelItf;
class DesignerMainWnd;

//! The abstract view class
class DesignerViewItf : public QWidget
{
    Q_OBJECT

    //constructor
protected:
    //! Constructor for initialization, should be called by children class constructors.
    DesignerViewItf(DesignerMainWnd* mainWnd, DesignerModelItf* model)
        :mainWindow(mainWnd){}

    //frame
public:
    //! Pointer to the frame this view currently belongs to.
    DesignerMainWnd* mainWindow;

    //model
public:
    //! Pointer to the document this view presents.
    DesignerModelItf* currentModel;

    //event slots
public slots:
    virtual void dataUpdated(){}
    virtual void storageUpdated(){}

protected:

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
    static DesignerViewItf* createView(QString viewName, DesignerMainWnd* mainWnd, DesignerModelItf* model);
    //! Retrieve the attributes of a view
    static QString getViewTitleByName(QString viewName);
    //! Retrieve the attributes of a view
    static QString getViewDefaultModelByName(QString viewName);
    //! Retrieve the attributes of a view
    static QMetaObject getViewMetaObjectByName(QString name);
};

Q_DECLARE_INTERFACE(DesignerViewItf, "com.ustcsoftware.Lachesis.ViewInterface/1.0")

#endif // DESIGNERVIEWITF_H
