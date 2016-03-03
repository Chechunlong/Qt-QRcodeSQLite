#ifndef DUPLICATE_H
#define DUPLICATE_H

#include <QDialog>
#include <sqlui.h>

namespace Ui {
class Duplicate;
}

class Duplicate : public QDialog
{
    Q_OBJECT

public:
    explicit Duplicate(QWidget *parent = 0);
    ~Duplicate();

private slots:
    void on_OK_clicked();

    void on_Cancel_clicked();

private:
    Ui::Duplicate *ui;
    SQLUI sqlui;

signals:
    void PWDPassed();
};

#endif // DUPLICATE_H
