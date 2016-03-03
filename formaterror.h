#ifndef FORMATERROR_H
#define FORMATERROR_H

#include <QDialog>
#include <sqlui.h>

namespace Ui {
class FormatError;
}

class FormatError : public QDialog
{
    Q_OBJECT

public:
    explicit FormatError(QWidget *parent = 0);
    ~FormatError();

private slots:
    void on_OK_clicked();

    void on_Cancel_clicked();

private:
    Ui::FormatError *ui;
    SQLUI sqlui;


signals:
    void PWDPassed();
};

#endif // FORMATERROR_H
