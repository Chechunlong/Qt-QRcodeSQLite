#include "formaterror.h"
#include "ui_formaterror.h"

FormatError::FormatError(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormatError)
{
    ui->setupUi(this);
    ui->PWD->setFocus();
}

FormatError::~FormatError()
{
    delete ui;
}

void FormatError::on_OK_clicked()
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

void FormatError::on_Cancel_clicked()
{
    ui->PWD->clear();
    ui->PWDStatus->clear();
//    this->close();
}
