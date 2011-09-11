#ifndef DESIGNERVIEWCOMPONENT_H
#define DESIGNERVIEWCOMPONENT_H

#include "DesignerViewItf.h"

//! The abstract view class
class DesignerViewComponent : public QWidget
                            , public DesignerViewItf
{
    Q_OBJECT
    Q_INTERFACES(DesignerViewItf)

    //constructor
protected:
    //! Constructor for initialization, should be called by children class constructors.
    DesignerViewComponent(DesignerMainWnd* mainWnd, DesignerModelComponent* model);

    //frame
public:
    //! Pointer to the frame this view currently belongs to.
    DesignerMainWnd* mainWindow;

    //model
public:
    //! Pointer to the document this view presents.
    DesignerModelComponent* currentModel;

    //signals

signals:
    void updateSelectedItem(QScriptValue);

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
    static DesignerViewComponent* createView(QString viewName, DesignerMainWnd* mainWnd, DesignerModelComponent* model);
    //! Retrieve the attributes of a view
    static QString getViewTitleByName(QString viewName);
    //! Retrieve the attributes of a view
    static QString getViewDefaultModelByName(QString viewName);
    //! Retrieve the attributes of a view
    static QMetaObject getViewMetaObjectByName(QString name);
};

#endif // DESIGNERVIEWCOMPONENT_H
