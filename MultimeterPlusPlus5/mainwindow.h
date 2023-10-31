#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialPort.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnConnect_clicked();

    void on_btnUpdatePorts_clicked();

    void on_btnClose_clicked();

    void readData(QString data);

    void on_btnSend_clicked();

private:
    Ui::MainWindow *ui;
    serialPort * _port;
    void showPorts();
};
#endif // MAINWINDOW_H
