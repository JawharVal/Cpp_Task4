#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QTextStream>
#include <QMap>
#include <QVector>

class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QString resultFilePath = "C:\\Users\\legion\\Downloads\\c++\\untitled1\\result.txt";
    QVBoxLayout *layout;
    QLabel *statusLabel;
    QLineEdit *sourceField, *synonymsField;
    QTextEdit *resultArea;
    QPushButton *sourceButton, *synonymsButton, *replaceButton;

    void setupUI();
    void setupField(QLineEdit *&field, QPushButton *&button, const QString &labelText);
    void setupConnections();
    void selectSourceFile();
    void selectSynonymsFile();
    void replaceWords();
    QMap<QString, QVector<QString>> parseSynonyms(QTextStream &stream);
    QString processText(const QString &text, const QMap<QString, QVector<QString>> &table);

};

#endif // MAINWINDOW_H
