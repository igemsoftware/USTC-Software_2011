#ifndef MAINWNDTABWIDGET_H
#define MAINWNDTABWIDGET_H

#include <QTabBar>
#include <QTabWidget>

class MainWndTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit MainWndTabWidget(QWidget *parent = 0);

    void protectPage(int index)
    {
        tabBar()->setTabButton(index, QTabBar::RightSide, 0);
    }

signals:

public slots:

};

#endif // MAINWNDTABWIDGET_H
