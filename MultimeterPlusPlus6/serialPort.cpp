#include "serialPort.h"

serialPort::serialPort(QObject *parent)
    : QObject{parent},
    _serialPort(nullptr)
{

}

serialPort::~serialPort()
{
    if(_serialPort != nullptr)
    {
        _serialPort->close();
        delete _serialPort;
    }
}

QStringList serialPort::loadPorts()
{
    QStringList portsList;
    portsList.clear();
    foreach(auto &_port, QSerialPortInfo::availablePorts())
    {
        portsList.append(_port.portName());
        qDebug() << "ports" << _port.portName() ;
    }
    return portsList;
}


bool serialPort::connectToPort(QString portName)
{
    _serialPort = new QSerialPort;
    _serialPort->setPortName(portName);
    _serialPort->setBaudRate(QSerialPort::Baud9600);
    _serialPort->setParity(QSerialPort::NoParity);
    _serialPort->setDataBits(QSerialPort::Data8);
    _serialPort->setStopBits(QSerialPort::OneStop);
    _serialPort->setFlowControl(QSerialPort::NoFlowControl);
    if(_serialPort->open(QIODevice::ReadWrite))
    {
        QObject::connect(_serialPort, &QSerialPort::readyRead, this, &serialPort::dataReady);
    }
    return _serialPort->isOpen();
    qDebug() << "Serialport: "<< portName << "is connected";
}

void serialPort::dataReady()
{
    if(_serialPort->isOpen())
    {
        while(_serialPort->bytesAvailable())
        {
            serialData += _serialPort->readAll();
        }
    }
    if(serialData.at(serialData.length() -1) == char(10))
    {
        dataReceived = true;
    }
    if (dataReceived == true)
    {
        emit data_Received(serialData);
        dataReceived = false;
        serialData = "";
    }
}

void serialPort::closePort()
{
    if(_serialPort->isOpen())
    {
        _serialPort->close();
        qDebug() << "closed port";
    }
    else
    {
        qDebug() << "no ports are open";
    }
}

qint64 serialPort::write(QString data)
{
    if(_serialPort == nullptr || !_serialPort->isOpen())
    {
        return -1;
    }
    return _serialPort->write(data.toLatin1() + char(10));
}
