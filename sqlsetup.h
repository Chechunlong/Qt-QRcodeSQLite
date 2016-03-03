#ifndef SQLSETUP_H
#define SQLSETUP_H

#include <QDialog>
#include <sqlui.h>

namespace Ui {
class SqlSetup;
}

class SqlSetup : public QDialog
{
    Q_OBJECT

public:
    explicit SqlSetup(QWidget *parent = 0);
    ~SqlSetup();

private slots:
    void on_OK_clicked();

    void on_Cancel_clicked();

private:
    Ui::SqlSetup *ui;
    SQLUI sqlui;
};

#endif // SQLSETUP_H
