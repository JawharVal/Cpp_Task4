#include "MainWindow.h"
#include "Logger.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Logger::logMessage("Application starting...", Logger::Info);

    MainWindow window;
    window.show();

    int result = app.exec();
    Logger::logMessage("Application exiting...", Logger::Info);
    return result;
}
