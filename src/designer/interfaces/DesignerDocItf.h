//! \file DesignerDocItf.h
//! Lachesis Designer Document Common Interface

#ifndef DesignerDOCComponent_H
#define DesignerDOCComponent_H

#include <QtCore>
#include "common/utils/itemregistry/ItemRegistry.h"
#include "DesignerDebug.h"

class DesignerMainWnd;
class DesignerModelComponent;

class DesignerDocItf
{
public:
    enum extentValue
    {
        NOTACCEPTABLE = 0,
        INSUFFICIENTLY = 1,
        EXCESSIVELY = 2,
        EXACTLY = 3
    };
    //! Check if the file is loadable by this type of document .
    virtual extentValue checkIfFileFitsDocumentType(QFile& file) = 0;
public:
    virtual bool loadFromFile(QFile& file) = 0;
    //! Dump data to this file. (implemented by subclasses)
    virtual bool saveToFile(QFile& file) = 0;
};

QT_BEGIN_NAMESPACE

Q_DECLARE_INTERFACE(DesignerDocItf, "com.ustcsoftware.Lachesis.DocumentInterface/1.0")

QT_END_NAMESPACE

#include "DesignerDocComponent.h"

#endif // DesignerDOCComponent_H
