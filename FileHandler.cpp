#include "FileHandler.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

QString FileHandler::readFile(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Error", "Failed to open file: " + filename);
        return QString();
    }
    QTextStream stream(&file);
    QString content = stream.readAll();
    file.close();
    return content;
}

bool FileHandler::writeFile(const QString &filename, const QString &content) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Error", "Failed to write file: " + filename);
        return false;
    }
    QTextStream stream(&file);
    stream << content;
    file.close();
    return true;
}
