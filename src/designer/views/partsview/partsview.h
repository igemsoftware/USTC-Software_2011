#ifndef PARTSVIEW_H
#define PARTSVIEW_H

#include <QWidget>

namespace Ui {
    class PartsView;
}

class PartsView : public QWidget
{
    Q_OBJECT

public:
    explicit PartsView(QWidget *parent = 0);
    ~PartsView();

private:
    Ui::PartsView *ui;
};

#endif // PARTSVIEW_H
