#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::WindowCloseButtonHint);
    ui->setupUi(this);
    this->setFixedSize(this->size());
    processChangedText = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_txtHex_textChanged()
{
    if(!processChangedText)
        return;

    static bool bProcess = true;
    if ((0 == ui->txtHex->toPlainText().length()) ||
            (0 != ui->txtHex->toPlainText().length()%2) ||
            !bProcess) {
        return;
    }
    processChangedText = bProcess = false;
    QTextCursor textCursor = ui->txtHex->textCursor();
    textCursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, textCursor.position());
    QString str = ui->txtHex->toPlainText();
    str.replace(" ","");
    ui->txtHex->setPlainText(str);
    str.clear();
    str = ui->txtHex->toPlainText();
    QString asciiStr;
    char asciiText[3]; asciiText[2] = '\0';
    for (int i = 0; i < ui->txtHex->toPlainText().length(); i+=2) {
        asciiText[0] = str.at(i).toLatin1();
        asciiText[1] = str.at(i+1).toLatin1();
        char c = strtol(asciiText, NULL, 16);
        asciiStr.append(c);
    }
    ui->txtASCII->setPlainText(asciiStr);
    ui->txtHex->setTextCursor(textCursor);
    processChangedText = bProcess = true;
}

void MainWindow::on_txtASCII_textChanged()
{
    static bool bProcess = true;

    if(!processChangedText || !bProcess)
        return;

    processChangedText = bProcess = false;
    QTextCursor textCursor = ui->txtASCII->textCursor();
    textCursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, textCursor.position());
    QString str = ui->txtASCII->toPlainText();
    QString hexStr;
    for(int i = 0; i < str.length(); i++) {
        char c = str.at(i).toLatin1();
        hexStr.append(QString::number(c));
    }
    ui->txtHex->setPlainText(hexStr);
    ui->txtASCII->setTextCursor(textCursor);
    processChangedText = bProcess = true;
}
