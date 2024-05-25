#include "Logger.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>

void Logger::logMessage(const QString &msg, LogLevel level) {
    QFile file("C:\\Users\\legion\\Downloads\\c++\\untitled1\\log.txt");  // Adjust path as necessary
    QString prefix;
    switch(level) {
        case Info: prefix = "INFO"; break;
        case Warning: prefix = "WARNING"; break;
        case Error: prefix = "ERROR"; break;
    }
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << QDateTime::currentDateTime().toString() << " - " << prefix << " - " << msg << "\n";
        file.close();
    }
}
