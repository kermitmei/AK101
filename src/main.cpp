#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    MainWindow   mainWindow;
    mainWindow.show();
    mainWindow.adjustHeaderWidth();
    return app.exec();
}
