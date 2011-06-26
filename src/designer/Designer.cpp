#include <QtGui/QApplication>
#include <QTextCodec>
#include "DesignerMainWnd.h"

int main(int argc, char *argv[])
{
    QApplication designer(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    DesignerMainWnd::globalCreateNewMainWnd();

    return designer.exec();
}
