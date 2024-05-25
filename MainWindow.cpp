#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include "MainWindow.h"
#include "FileHandler.h"
#include "Logger.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
    Logger::logMessage("This is an information message", Logger::Info);
    Logger::logMessage("This is a warning message", Logger::Warning);
    Logger::logMessage("This is an error message", Logger::Error);
}

void MainWindow::setupUI() {
    this->setWindowTitle("Synonym Replacer");
    layout = new QVBoxLayout(this);
    statusLabel = new QLabel("Ready to load files.");
    layout->addWidget(statusLabel);

    setupField(sourceField, sourceButton, "Source file:");
    setupField(synonymsField, synonymsButton, "Synonyms file:");

    QLabel *resultLabel = new QLabel("Result:");
    layout->addWidget(resultLabel);
    resultArea = new QTextEdit;
    layout->addWidget(resultArea);

    replaceButton = new QPushButton("Replace words");
    layout->addWidget(replaceButton);
}

void MainWindow::setupField(QLineEdit *&field, QPushButton *&button, const QString &labelText) {
    QLabel *label = new QLabel(labelText);
    layout->addWidget(label);
    field = new QLineEdit;
    layout->addWidget(field);
    button = new QPushButton("Browse...");
    layout->addWidget(button);
}

void MainWindow::setupConnections() {
    connect(sourceButton, &QPushButton::clicked, this, &MainWindow::selectSourceFile);
    connect(synonymsButton, &QPushButton::clicked, this, &MainWindow::selectSynonymsFile);
    connect(replaceButton, &QPushButton::clicked, this, &MainWindow::replaceWords);
}

void MainWindow::selectSourceFile() {
    QString filename = QFileDialog::getOpenFileName(this, "Open Source File");
    sourceField->setText(filename);
    statusLabel->setText(!filename.isEmpty() ? "Source file loaded." : "Source file loading canceled.");
}

void MainWindow::selectSynonymsFile() {
    QString filename = QFileDialog::getOpenFileName(this, "Open Synonyms File");
    synonymsField->setText(filename);
    statusLabel->setText(!filename.isEmpty() ? "Synonyms file loaded." : "Synonyms file loading canceled.");
}

void MainWindow::replaceWords() {
    QString sourceFilename = sourceField->text();
    QString synonymsFilename = synonymsField->text();

    Logger::logMessage("Attempting to load source file.", Logger::Info);
    QString sourceText = FileHandler::readFile(sourceFilename);
    if (sourceText.isEmpty()) {
        Logger::logMessage("Failed to load source file.", Logger::Error);
        QMessageBox::warning(this, "Error", "Cannot read source file.");
        return;
    }

    Logger::logMessage("Attempting to load synonyms file.", Logger::Info);
    QString synonymsData = FileHandler::readFile(synonymsFilename);
    if (synonymsData.isEmpty()) {
        Logger::logMessage("Failed to load synonyms file.", Logger::Error);
        QMessageBox::warning(this, "Error", "Cannot read synonyms file.");
        return;
    }

    // Convert QString to QTextStream
    QTextStream synonymsStream(&synonymsData);
    QMap<QString, QVector<QString>> synonymsTable = parseSynonyms(synonymsStream);
    QString resultText = processText(sourceText, synonymsTable);

    Logger::logMessage("Saving processed result.", Logger::Info);
    if (FileHandler::writeFile(resultFilePath, resultText)) { // Use the path member variable
        Logger::logMessage("Result saved successfully.", Logger::Info);
    } else {
        Logger::logMessage("Failed to save result file.", Logger::Error);
    }

    resultArea->setText(resultText);
    statusLabel->setText("Operation completed successfully. Check the result.");
}

QMap<QString, QVector<QString>> MainWindow::parseSynonyms(QTextStream &stream) {
    QMap<QString, QVector<QString>> table;
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList parts = line.split(" ");
        if (parts.size() >= 2) {
            QString word = parts.first();
            QVector<QString> synonyms(parts.begin() + 1, parts.end());
            table.insert(word, synonyms);
        }
    }
    return table;
}

QString MainWindow::processText(const QString &text, const QMap<QString, QVector<QString>> &table) {
    QStringList words = text.split(" ", Qt::SkipEmptyParts);
    QString resultText;
            foreach (const QString &word, words) {
            QVector<QString> synonyms = table.value(word);
            if (!synonyms.isEmpty()) {
                int randomIndex = rand() % synonyms.size();
                resultText += synonyms[randomIndex] + " ";
            } else {
                resultText += word + " ";
            }
        }
    return resultText.trimmed();
}


