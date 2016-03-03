#ifndef SERIALSETUP_H
#define SERIALSETUP_H

#include <QDialog>
#include <QDebug>
#include <serial.h>

namespace Ui {
class SerialSetup;
}

class SerialSetup : public QDialog
{
    Q_OBJECT

public:
    explicit SerialSetup(QWidget *parent = 0);
    ~SerialSetup();

private slots:
    void GetSerialport();
    void on_OK_clicked();

    void on_Cancel_clicked();

private:
    Ui::SerialSetup *ui;
    Serial serialport;
};

#endif // SERIALSETUP_H
