#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_txtHex_textChanged();

    void on_txtASCII_textChanged();

private:
    Ui::MainWindow *ui;
    bool processChangedText;
};

#endif // MAINWINDOW_H
