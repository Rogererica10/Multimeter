#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    _port = new serialPort(this);
    ui->setupUi(this);
    connect(_port, &serialPort::data_Received, this, &MainWindow::readData);

    showPorts();
    //showData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnConnect_clicked()
{
    if (_port->connectToPort(ui->cmbPorts->currentText()))

    {
        QString output = "conected to " + ui->cmbPorts->currentText();
        ui->labelConnected->setText(output);
    }
    else ui->labelConnected->setText("not connected");
}

void MainWindow::on_btnUpdatePorts_clicked()
{
    ui->cmbPorts->clear();
    showPorts();
}

void MainWindow::showPorts()
{
    ui->cmbPorts->addItems(_port->loadPorts());
}

void MainWindow::on_btnClose_clicked()
{
    _port->closePort();
    ui->labelConnected->setText("disconnected");
}

void MainWindow::readData(QString data)
{

    ui->teReceived->append(data);
    ui->lcdData->display(data.toLatin1());
    qDebug() << "measurement: " << data;
}

void MainWindow::on_btnSend_clicked()
{
    _port->write(ui->leSendData->text());
}

