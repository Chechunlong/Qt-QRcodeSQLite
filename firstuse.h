#ifndef FIRSTUSE_H
#define FIRSTUSE_H

#include <QDialog>

namespace Ui {
class FirstUSE;
}

class FirstUSE : public QDialog
{
    Q_OBJECT

public:
    explicit FirstUSE(QWidget *parent = 0);
    ~FirstUSE();

private:
    Ui::FirstUSE *ui;
};

#endif // FIRSTUSE_H
