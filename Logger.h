#ifndef LOGGER_H
#define LOGGER_H

#include <QString>

class Logger {
public:
    enum LogLevel { Info, Warning, Error };
    static void logMessage(const QString &msg, LogLevel level);
};

#endif // LOGGER_H
