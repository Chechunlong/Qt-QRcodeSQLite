#include "serial.h"

QSerialPort serial;
int Connum = 0;
Serial::Serial()
{
    connect(&serial, SIGNAL(readyRead()), this, SLOT(readData()));
}

bool Serial::OpenSerial(QString SerialName,int Baudrate)
{
    serial.setPortName(SerialName);
    serial.setBaudRate(Baudrate);
    if(serial.open(QIODevice::ReadWrite))
    {
        qDebug() <<SerialName<<" is opened!";
        return true;
    }
    else
    {
        return false;
    }
}

void Serial::readData()
{
    if (serial.waitForReadyRead(5)){
        QByteArray data = serial.readAll();
        QString string(data);
        if(string != NULL)
        {
            emit SerialData(string);
        }
    }
}
