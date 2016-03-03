#include "duplicate.h"
#include "ui_duplicate.h"

Duplicate::Duplicate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Duplicate)
{
    ui->setupUi(this);
    ui->PWD->setFocus();
}

Duplicate::~Duplicate()
{
    delete ui;
}

void Duplicate::on_OK_clicked()
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

void Duplicate::on_Cancel_clicked()
{
    ui->PWD->clear();
    ui->PWDStatus->clear();
//    this->close();
}
