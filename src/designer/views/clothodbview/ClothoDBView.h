#ifndef CLOTHODBVIEW_H
#define CLOTHODBVIEW_H

#include <QtGui>
#include <QtCore>
#include <QXmlSimpleReader>
#include <QDesktopServices>

#include "DesignerViewItf.h"


namespace Ui {
    class ClothoDBView;
}

class ClothoDBView : public DesignerViewItf
{
    Q_OBJECT
    QXmlSimpleReader xmlReader;
    QXmlInputSource *source;

public:
    void initiate();
    void connect();

    Q_INVOKABLE explicit ClothoDBView(DesignerMainWnd *mainWnd);
    ~ClothoDBView();

private:
    Ui::ClothoDBView *ui;
};

#endif // CLOTHODBVIEW_H
