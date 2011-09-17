//! \file DesignerExtensionItf.h
//! Lachesis Designer Extension Common Interface

#ifndef DESIGNEREXTENSIONITF_H
#define DESIGNEREXTENSIONITF_H

#include <QtCore>

class DesignerExtensionItf
{
public:
    virtual const QMetaObject* extensionMetaObject() = 0;
    virtual bool initialize() = 0;

};

Q_DECLARE_INTERFACE(DesignerExtensionItf, "com.ustcsoftware.Lachesis.ModelInterface/1.0")


#endif // DESIGNEREXTENSIONITF_H
