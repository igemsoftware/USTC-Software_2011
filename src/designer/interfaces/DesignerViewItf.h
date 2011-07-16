#ifndef DESIGNERVIEWITF_H
#define DESIGNERVIEWITF_H

#include <QtGui>
#include "common/utils/itemregistry/ItemRegistry.h"

class DesignerMainWnd;

//! The abstract view class
class DesignerViewItf : public QWidget
{
    Q_OBJECT
public:
    DesignerViewItf(DesignerMainWnd* mainWnd)
        :mainWindow(mainWnd){}

public:
    DesignerMainWnd* mainWindow;
protected:

public:
    struct ViewItfRegistryItem
    {
        QMetaObject metaObject;
        QString     viewTitle;


        ViewItfRegistryItem() { ViewItfRegistryItem(DesignerViewItf::staticMetaObject, "Invalid"); }

        ViewItfRegistryItem(QMetaObject m ,QString v) : metaObject(m), viewTitle(v) {}
     };

    typedef ItemRegistry<QString, ViewItfRegistryItem> ViewItfRegistry;
public:
    static DesignerViewItf* createView(QString, DesignerMainWnd* mainWnd);

    static QString getViewTitleByName(QString name);
    static QMetaObject getViewMetaObjectByName(QString name);

};

#define LACHESIS_DECLARE_VIEW(className, titleString) \
    DesignerViewItf::ViewItfRegistry::ItemRegistryInlineAdd viewreg_##className (QString( #className ), \
    DesignerViewItf::ViewItfRegistryItem( className ::staticMetaObject, QObject::tr(titleString)))


#endif // DESIGNERVIEWITF_H
