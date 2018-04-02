#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << QCoreApplication::applicationDirPath();

    DatabaseManager::instance();
    DatabaseManager::instance();
    DatabaseManager::instance();

    MainWindow w;
    w.show();

    return a.exec();
}
