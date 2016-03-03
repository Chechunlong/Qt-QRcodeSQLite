#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <sqlui.h>
#include <inputpwd.h>
#include <serial.h>
#include <serialsetup.h>
#include <QTime>
#include <QtXlsx>
#include <formaterror.h>
#include <duplicate.h>
#include <numbererror.h>
#include <sqlsetup.h>
#include <help.h>
#include <inputarg.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    SQLUI sqlui;
    InputPWD inputPWD;
    Serial serialPort;
    SerialSetup serialsetup;
    FormatError formatError;
    Duplicate duplicate;
    NumberError numberError;
    SqlSetup sqlsetup;
    Help help;
    InputArg inputarg;

private slots:
    void uiToData();
    void PWDPassed_Index();
    void PWDPassed();
    void DisableWidget();
    void on_ChangeButton_clicked();
    void on_Query_clicked();
    void on_Save_clicked();
    void GetSerialData(QString);
    void SaveDataToEXL();
    void clearUI();
    void InitStatus();
    void SetStatus(int number,bool status);
    void OpenPath();
};

#endif // MAINWINDOW_H
