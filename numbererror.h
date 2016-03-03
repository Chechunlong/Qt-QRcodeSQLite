#ifndef NUMBERERROR_H
#define NUMBERERROR_H

#include <QDialog>
#include <sqlui.h>

namespace Ui {
class NumberError;
}

class NumberError : public QDialog
{
    Q_OBJECT

public:
    explicit NumberError(QWidget *parent = 0);
    ~NumberError();

private slots:
    void on_OK_clicked();

    void on_Cancel_clicked();

private:
    Ui::NumberError *ui;
    SQLUI sqlui;

signals:
    void PWDPassed();
};

#endif // NUMBERERROR_H
