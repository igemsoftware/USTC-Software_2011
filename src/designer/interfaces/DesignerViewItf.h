//! \file DesignerViewItf.h
//! Lachesis Designer View Common Interface

#ifndef DesignerVIEWComponent_H
#define DesignerVIEWComponent_H

#include <QtCore>
#include <QtGui>
#include <QtScript>
#include "common/utils/itemregistry/ItemRegistry.h"

class DesignerModelComponent;
class DesignerMainWnd;

class DesignerViewItf
{
public:
    virtual void dataUpdated() = 0;
    virtual void storageUpdated() = 0;
};

QT_BEGIN_NAMESPACE

Q_DECLARE_INTERFACE(DesignerViewItf, "com.ustcsoftware.Lachesis.ViewInterface/1.0")

QT_END_NAMESPACE

#include "DesignerViewComponent.h"

#endif // DesignerVIEWComponent_H
