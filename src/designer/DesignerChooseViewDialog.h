#ifndef DESIGNERCHOOSEVIEWDIALOG_H
#define DESIGNERCHOOSEVIEWDIALOG_H

#include <QDialog>

namespace Ui {
    class ChooseViewDialog;
}

class ChooseViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseViewDialog(QWidget *parent = 0, QList<QString> viewList = QList<QString>());
    ~ChooseViewDialog();

    int getChoosenViewIndex();
private:
    Ui::ChooseViewDialog *ui;
};

#endif // DESIGNERCHOOSEVIEWDIALOG_H
