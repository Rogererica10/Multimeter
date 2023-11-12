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
    ui->plot->addGraph();
    ui->plot->graph()->setLineStyle(QCPGraph::lsLine);
    ui->plot->xAxis->setLabel("Time");
    ui->plot->xAxis->setRange(0, 7);
    ui->plot->yAxis->setLabel("Voltage");
    ui->plot->yAxis->setRange(-1000, 1000);


    time = 0.0;

    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &MainWindow::updateDiagram);
    //connect(, SIGNAL (valueChanged()),ui->plot, &MainWindow::updateDiagram);
    _timer->start(100);
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
    ui->lcdData->display(data.toDouble());
    qDebug() << "measurement: " << data;
    *_data = data.toDouble();
}

void MainWindow::on_btnSend_clicked()
{
    _port->write(ui->leSendData->text());
}

void MainWindow::updateDiagram()
{
    time += 0.1;
    ui->plot->graph()->addData(time, *_data);
    if(time > 6)
    {
        ui->plot->xAxis->setRange(time - 6, time +5);
    }
    /*if(*_data > 1900)
    {
        ui->plot->yAxis->setRange(*_data - 1900, *_data +1000);
    }*/

    ui->plot->replot();
    ui->plot->update();

}
