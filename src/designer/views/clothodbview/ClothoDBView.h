#ifndef CLOTHODBVIEW_H
#define CLOTHODBVIEW_H

#include <QtGui>
#include <QtCore>
#include <QXmlSimpleReader>
#include <QDesktopServices>

namespace Ui {
    class ClothoDBView;
}

class ClothoDBView : public QWidget
{
    Q_OBJECT
    QXmlSimpleReader xmlReader;
    QXmlInputSource *source;

public:
    void initiate();
    void connect();

    explicit ClothoDBView(QWidget *parent = 0);
    ~ClothoDBView();

private:
    Ui::ClothoDBView *ui;
};

#endif // CLOTHODBVIEW_H
