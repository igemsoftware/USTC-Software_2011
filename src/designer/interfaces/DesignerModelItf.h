//! \file DesignerModelItf.h
//! Lachesis Designer Model Common Interface

#ifndef DesignerMODELComponent_H
#define DesignerMODELComponent_H

#include <QtCore>
#include <QtScript>
#include "common/utils/itemregistry/ItemRegistry.h"

class DesignerDocComponent;

class DesignerModelItf
{
    //display support
public:
    //! Retrive the name of views this model DIRECTLY SUPPORTS.
    //! Notice that the views supported by the submodels
    //! should not appear here.
    virtual QStringList getSupportedViewList() const = 0;
    virtual QStringList getSupportedDocumentList() const = 0;

};

QT_BEGIN_NAMESPACE

Q_DECLARE_INTERFACE(DesignerModelItf, "com.ustcsoftware.Lachesis.ModelInterface/1.0")

QT_END_NAMESPACE


#include "DesignerModelComponent.h"

#endif // DesignerMODELComponent_H
