#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>
#include <QDir>

QList<QTextBrowser *> ProductNumber;
QList<QLineEdit *> QRcode;
QList<QLabel *> Status;
bool changeInfoFlag = false;
QXlsx::Document xlsx;
QString ProductTime[32];
QString FilePath = "C:/Users/Administrator/Documents/QREXLFile/";
bool StopFlag = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDir dir;
    bool exist = dir.exists(FilePath);
    if(!exist)
    {
        dir.mkpath(FilePath);
    }
    connect(&inputPWD,SIGNAL(PWDPassed()),this,SLOT(PWDPassed_Index()));
    connect(&duplicate,SIGNAL(PWDPassed()),this,SLOT(PWDPassed()));
    connect(&formatError,SIGNAL(PWDPassed()),this,SLOT(PWDPassed()));
    connect(&numberError,SIGNAL(PWDPassed()),this,SLOT(PWDPassed()));
    connect(ui->action,SIGNAL(triggered()),&sqlsetup,SLOT(show()));
    connect(ui->action_5,SIGNAL(triggered()),&serialsetup,SLOT(show()));
    connect(ui->action_excel,SIGNAL(triggered()),this,SLOT(OpenPath()));
    connect(ui->action_2,SIGNAL(triggered()),&sqlui,SLOT(InitDB()));
    connect(ui->action_7,SIGNAL(triggered()),&sqlui,SLOT(show()));
    connect(ui->action_10,SIGNAL(triggered()),&help,SLOT(show()));
    connect(&serialPort,SIGNAL(SerialData(QString)),this,SLOT(GetSerialData(QString)));
    uiToData();
    DisableWidget();
    InitStatus();
    ui->ProductName->setPlaceholderText(tr("请设置产品名称"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PWDPassed_Index()
{
    ui->ProductName->setDisabled(false);
    ui->HeadData->setDisabled(false);
    ui->TailData->setDisabled(false);
    ui->ChangeButton->setText(tr("确定"));
    ui->ChangeButton->setFont(QFont("Adobe Arabic",20));
    StopFlag = true;
}

void MainWindow::PWDPassed()
{
    StopFlag = true;
}

void MainWindow::DisableWidget()
{
    ui->ProductName->setDisabled(true);
    ui->HeadData->setDisabled(true);
    ui->TailData->setDisabled(true);
    ui->ChangeButton->setText(tr("修改"));
    ui->ChangeButton->setFont(QFont("Adobe Arabic",20));
}

void MainWindow::on_ChangeButton_clicked()
{
    if(changeInfoFlag)
    {
        DisableWidget();
        changeInfoFlag = false;
    }
    else
    {
        StopFlag = true;
        inputPWD.show();
        changeInfoFlag = true;
    }
}

void MainWindow::on_Query_clicked()
{
    sqlui.show();
}

void MainWindow::on_Save_clicked()
{
    SaveDataToEXL();
    clearUI();
}

void MainWindow::GetSerialData(QString data)
{
    QString Arg1,Arg2,Arg3,Arg4;
    bool Arg;
    Arg1 = ui->ProductName->text();
    Arg2 = ui->BoxNumber->text();
    Arg3 = ui->HeadData->text();
    Arg4 = ui->TailData->text();
    if(Arg1 != NULL)
    {
        if(Arg2 != NULL)
        {
            if(Arg3 != NULL)
            {
                if(Arg4 != NULL)
                {
                    Arg = true;
                }
                else Arg = false;
            }
            else Arg = false;
        }
        else Arg = false;
    }
    else Arg = false;
    data = data.trimmed();
    //去除字符串最后\r\n如果出问题请更改

    QString TableName = "QRCODE";
    QString column = "QRCode";
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyyMMddhhmmss");
    QStringList DataToSQL,QRKEY;
    QRKEY<<"time"<<"ProductName"<<"BoxNumber"<<"QRCode"<<"Status";

    //正则表达式,验证data的合法性
    QRegExp rx("^"+ui->HeadData->text()+".*"+ui->TailData->text()+"$");
    //Check Data format
    rx.setPatternSyntax(QRegExp::RegExp);
    bool match = rx.exactMatch(data);

    //这里开始验证重码,如果有重复返回true
    bool repeat = sqlui.CheckRepeat(TableName,column,data);

    if(Arg)
    {
        if(StopFlag)
        {
            if(!repeat)
            {
                if(match)
                {
                    for(int i = 0;i<32;i++)
                    {
                        if(QRcode[i]->text() == NULL)
                        {
                            QRcode[i]->setText(data);
                            ProductTime[i] = current_date;
                            QRcode[i]->setFont(QFont("Adobe Arabic",20));
                            SetStatus(i,true);
                            QRcode[i]->setDisabled(true);
                            DataToSQL<<current_date<<ui->ProductName->text()<<ui->BoxNumber->text()<<data<<"OK";
                            //插入到数据库，请在此操作之前判定数据格式是否正确
                            sqlui.insert(TableName,QRKEY,DataToSQL);
                            break;
                        }
                    }
                }else
                {
                    StopFlag = false;
                    formatError.show();
                }
            }else
            {
                StopFlag = false;
                duplicate.show();
            }
        }
    }else
    {
        StopFlag = false;
        inputarg.show();
    }
}

void MainWindow::SaveDataToEXL()
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyyMMddhhmmss");
    QString FileName = FilePath+current_date+"-BN"+ui->BoxNumber->text()+".xlsx";

    for(int i = 0;i<33;i++)
    {
        if(i == 0)
        {
            xlsx.write(1,1,tr("时间"));
            xlsx.write(1,2,tr("产品名称"));
            xlsx.write(1,3,tr("产品箱号"));
            xlsx.write(1,4,tr("产品二维码"));
            xlsx.write(1,5,tr("产品状态"));
        }else
        {
            if(QRcode[i-1]->text() != NULL)
            {
                xlsx.write(i+1,1,ProductTime[i-1]);
                xlsx.write(i+1,2,ui->ProductName->text());
                xlsx.write(i+1,3,ui->BoxNumber->text());
                xlsx.write(i+1,4,QRcode[i-1]->text());
                xlsx.write(i+1,5,Status[i-1]->text());
            }
            else
            {
                xlsx.saveAs(FileName);
                break;
            }
        }
    }
    xlsx.saveAs(FileName);
}

void MainWindow::clearUI()
{
    for(int i = 0;i<32;i++)
    {
        SetStatus(i,false);
        ProductTime[i] = "";
        QRcode[i]->setDisabled(false);
        QRcode[i]->clear();
    }
}

void MainWindow::uiToData()
{
    ProductNumber<<ui->Number_1<<ui->Number_2<<ui->Number_3<<ui->Number_4<<ui->Number_5\
                   <<ui->Number_6<<ui->Number_7<<ui->Number_8<<ui->Number_9<<ui->Number_10\
                     <<ui->Number_11<<ui->Number_12<<ui->Number_13<<ui->Number_14<<ui->Number_15\
                       <<ui->Number_16<<ui->Number_17<<ui->Number_18<<ui->Number_19<<ui->Number_20\
                         <<ui->Number_21<<ui->Number_22<<ui->Number_23<<ui->Number_24<<ui->Number_25\
                           <<ui->Number_26<<ui->Number_27<<ui->Number_28<<ui->Number_29<<ui->Number_30\
                             <<ui->Number_31<<ui->Number_32;
    QRcode<<ui->QRcode_1<<ui->QRcode_2<<ui->QRcode_3<<ui->QRcode_4<<ui->QRcode_5<<ui->QRcode_6\
            <<ui->QRcode_7<<ui->QRcode_8<<ui->QRcode_9<<ui->QRcode_10<<ui->QRcode_11<<ui->QRcode_12\
              <<ui->QRcode_13<<ui->QRcode_14<<ui->QRcode_15<<ui->QRcode_16<<ui->QRcode_17<<ui->QRcode_18\
                <<ui->QRcode_19<<ui->QRcode_20<<ui->QRcode_21<<ui->QRcode_22<<ui->QRcode_23<<ui->QRcode_24\
                  <<ui->QRcode_25<<ui->QRcode_26<<ui->QRcode_27<<ui->QRcode_28<<ui->QRcode_29<<ui->QRcode_30\
                    <<ui->QRcode_31<<ui->QRcode_32;
    Status<<ui->Status_1<<ui->Status_2<<ui->Status_3<<ui->Status_4<<ui->Status_5<<ui->Status_6<<ui->Status_7\
            <<ui->Status_8<<ui->Status_9<<ui->Status_10<<ui->Status_11<<ui->Status_12<<ui->Status_13<<ui->Status_14\
              <<ui->Status_15<<ui->Status_16<<ui->Status_17<<ui->Status_18<<ui->Status_19<<ui->Status_20\
                <<ui->Status_21<<ui->Status_22<<ui->Status_23<<ui->Status_24<<ui->Status_25<<ui->Status_26\
                  <<ui->Status_27<<ui->Status_28<<ui->Status_29<<ui->Status_30<<ui->Status_31<<ui->Status_32;
}

void MainWindow::InitStatus()
{
    for(int i = 0;i<32;i++)
    {
        SetStatus(i,false);
    }
}

void MainWindow::SetStatus(int number,bool status)
{
    QPalette pe;
    if(status)
    {
        pe.setColor(QPalette::WindowText,Qt::green);
        Status[number]->setText("OK");
        Status[number]->setFont(QFont("Adobe Arabic",20));
        Status[number]->setPalette(pe);
    }else
    {
        pe.setColor(QPalette::WindowText,Qt::red);
        Status[number]->setText("NG");
        Status[number]->setFont(QFont("Adobe Arabic",20));
        Status[number]->setPalette(pe);
    }
}

void MainWindow::OpenPath()
{
    QDesktopServices::openUrl(QUrl(FilePath, QUrl::TolerantMode));
}
