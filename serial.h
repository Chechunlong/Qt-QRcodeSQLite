#ifndef SERIAL_H
#define SERIAL_H

#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>

class Serial:public QObject
{
    Q_OBJECT

public:
    Serial();
    bool OpenSerial(QString SerialName,int Baudrate);

private slots:
    void readData();

signals:
    void SerialData(QString);
};

#endif // SERIAL_H
