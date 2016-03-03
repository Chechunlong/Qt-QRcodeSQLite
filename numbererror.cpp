#include "numbererror.h"
#include "ui_numbererror.h"

NumberError::NumberError(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NumberError)
{
    ui->setupUi(this);
    ui->PWD->setFocus();
}

NumberError::~NumberError()
{
    delete ui;
}

void NumberError::on_OK_clicked()
{
    if(sqlui.CheckPWD(ui->PWD->text()))
    {
        ui->PWD->clear();
        ui->PWDStatus->clear();
        emit PWDPassed();
        this->close();
    }else
    {
        ui->PWDStatus->setText(tr("密码错误！"));
    }
}

void NumberError::on_Cancel_clicked()
{
    ui->PWD->clear();
    ui->PWDStatus->clear();
//    this->close();
}
