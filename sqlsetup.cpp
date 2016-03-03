#include "sqlsetup.h"
#include "ui_sqlsetup.h"

SqlSetup::SqlSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SqlSetup)
{
    ui->setupUi(this);
}

SqlSetup::~SqlSetup()
{
    delete ui;
}

void SqlSetup::on_OK_clicked()
{
    if(sqlui.CheckPWD(ui->PWD->text()))
    {
        QString PWD,PWD1;
        PWD = ui->NewPWD->text();
        PWD1 = ui->NewPWD1->text();
        if(PWD == PWD1)
        {
            qDebug() << "ChangePWD";
            QString Table = "USER";
            QString expression = "USER = 'Admin'";
            QStringList name,value;
            name<<"PASSWD";
            value<<ui->NewPWD->text();
            sqlui.Updata(Table,name,value,expression);
            ui->PWD->clear();
            ui->NewPWD->clear();
            ui->NewPWD1->clear();
            ui->PWDStatus->clear();
            this->close();
        }else
        {
            ui->PWD->clear();
            ui->NewPWD->clear();
            ui->NewPWD1->clear();
            ui->PWDStatus->setText(tr("两次密码不一致！"));
        }
    }else
    {
        ui->PWD->clear();
        ui->NewPWD->clear();
        ui->NewPWD1->clear();
        ui->PWDStatus->setText(tr("密码错误！"));
    }
}

void SqlSetup::on_Cancel_clicked()
{
    ui->PWD->clear();
    ui->NewPWD->clear();
    ui->NewPWD1->clear();
    ui->PWDStatus->clear();
}
