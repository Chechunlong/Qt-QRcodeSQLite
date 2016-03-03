#include "firstuse.h"
#include "ui_firstuse.h"

FirstUSE::FirstUSE(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FirstUSE)
{
    ui->setupUi(this);
}

FirstUSE::~FirstUSE()
{
    delete ui;
}
