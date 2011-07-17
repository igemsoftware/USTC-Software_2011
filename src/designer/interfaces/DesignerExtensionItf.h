//! \file DesignerExtensionItf.h
//! Lachesis Designer Extension Common Interface

#ifndef DESIGNEREXTENSIONITF_H
#define DESIGNEREXTENSIONITF_H

#include <QtCore>

class DesignerExtensionItf : public QObject
{
    Q_OBJECT
public:
    explicit DesignerExtensionItf(QObject *parent = 0);

    enum ExtensionDisplayLevel
    {
        DisplayAsStandaloneFrame,
        DisplayAsModalDialog,
        DisplayAsModelessDialog,
        DisplayAsView,
        DisplayAsButton,
        DisplayAsNothing
    };

    enum ExtensionInvokeType
    {
        NewModel           = 1,
        NewDocument        = 2,
        NewView            = 4,
        NewMenuItem        = 8,
        NewToolBarButton   = 16,
        NewViewHook        = 32
    };

signals:

public slots:

};

#endif // DESIGNEREXTENSIONITF_H
