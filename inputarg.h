#ifndef INPUTARG_H
#define INPUTARG_H

#include <QDialog>

namespace Ui {
class InputArg;
}

class InputArg : public QDialog
{
    Q_OBJECT

public:
    explicit InputArg(QWidget *parent = 0);
    ~InputArg();

private slots:
    void on_OK_clicked();

private:
    Ui::InputArg *ui;

signals:
    void PWDPassed();
};

#endif // INPUTARG_H
