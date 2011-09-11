#ifndef DESIGNERVIEWCOMPONENT_H
#define DESIGNERVIEWCOMPONENT_H

#include "DesignerViewItf.h"

#include "common/componentmgr/DesignerViewMgr.h"

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
};

#endif // DESIGNERVIEWCOMPONENT_H
