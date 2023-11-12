#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QDebug>

class serialPort :public QObject
{
    Q_OBJECT
private:

    QString serialData;
    QSerialPort *_serialPort;
    bool dataReceived;

private slots:
   void dataReady();

signals:
   void data_Received(QString);

public:
    explicit serialPort(QObject *parent = nullptr);
    ~serialPort();
    QStringList loadPorts();
    void closePort();
    bool connectToPort(QString portName);
    qint64 write(QString data);
};

#endif // SERIALPORT_H
