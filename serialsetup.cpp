#include "serialsetup.h"
#include "ui_serialsetup.h"

SerialSetup::SerialSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialSetup)
{
    ui->setupUi(this);
    GetSerialport();
}

SerialSetup::~SerialSetup()
{
    delete ui;
}

void SerialSetup::GetSerialport()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Name : " << info.portName();
        QSerialPort serial;
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
            {
                serial.close();
                ui->SerialPort->addItem(info.portName());
            }
    }
}

void SerialSetup::on_OK_clicked()
{
    int baud = ui->BaudRate->currentText().toInt();
    bool SerialResault = serialport.OpenSerial(ui->SerialPort->currentText(),baud);
    if(SerialResault)
    {
        this->close();
    }else
    {
        ui->SerialStatus->setText(tr("串口打开失败，或已经打开！"));
    }
}

void SerialSetup::on_Cancel_clicked()
{
    this->close();
}
