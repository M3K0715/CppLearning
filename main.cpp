#include "mainwidget.h"
#include "enterdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EnterDialog dialog;
    dialog.show();

#if 0
    MainWidget w;
    w.show();
#endif
    return a.exec();
}
