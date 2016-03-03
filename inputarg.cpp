#include "inputarg.h"
#include "ui_inputarg.h"

InputArg::InputArg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputArg)
{
    ui->setupUi(this);
}

InputArg::~InputArg()
{
    delete ui;
}

void InputArg::on_OK_clicked()
{
    emit PWDPassed();
    this->close();
}
