#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(rc);
    MainWindow w;
    w.setWindowIcon(QIcon(":/ressources/rIcon"));
    w.show();
    
    return a.exec();
}
