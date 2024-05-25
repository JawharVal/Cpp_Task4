#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QString>

class FileHandler {
public:
    static QString readFile(const QString &filename);
    static bool writeFile(const QString &filename, const QString &content);
};

#endif // FILEHANDLER_H
