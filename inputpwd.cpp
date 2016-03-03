#include "inputpwd.h"
#include "ui_inputpwd.h"

InputPWD::InputPWD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputPWD)
{
    ui->setupUi(this);
    ui->PWD->setFocus();
}

InputPWD::~InputPWD()
{
    delete ui;
}

void InputPWD::on_OK_clicked()
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

void InputPWD::on_Cancel_clicked()
{
    ui->PWD->clear();
    ui->PWDStatus->clear();
//    this->close();
}
