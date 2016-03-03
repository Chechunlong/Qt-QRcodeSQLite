#ifndef INPUTPWD_H
#define INPUTPWD_H

#include <QDialog>
#include <sqlui.h>

namespace Ui {
class InputPWD;
}

class InputPWD : public QDialog
{
    Q_OBJECT

public:
    explicit InputPWD(QWidget *parent = 0);
    ~InputPWD();

signals:
    void PWDPassed();

private slots:
    void on_OK_clicked();
    void on_Cancel_clicked();

private:
    Ui::InputPWD *ui;
    SQLUI sqlui;
};

#endif // INPUTPWD_H
