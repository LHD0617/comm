/**
 * @file mainwindow.cpp
 * @author 主窗口
 * @brief 
 * @version 0.1
 * @date 2023-02-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* @include */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "comm.h"
#include <QIntValidator>
#include <QMutex>
#include <QDebug>

static MainWindow* thispt;
QMutex fifo_mutex;
QTimer autoTimer;

/* @Function declarations */
static QString ByteArrayToHexString(QByteArray ascii);
static char ConvertCharToHex(char ch);
static QByteArray HexStringToQByteArray(QString str);
static void tag_callback(uint16_t len, uint8_t* value);

/**
 * @brief Construct a new Main Window:: Main Window object
 * 
 * @param parent 
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    thispt = this;

    ui->tagLedit->setValidator(new QIntValidator(0, 999, this));

    connect(ui->sendPbtn, SIGNAL(clicked()), this, SLOT(sendFrame()));
    connect(ui->tagLedit, SIGNAL(returnPressed()), ui->sendPbtn, SLOT(click()), Qt::UniqueConnection);
    connect(ui->valueLedit, SIGNAL(returnPressed()), ui->sendPbtn, SLOT(click()), Qt::UniqueConnection);
    connect(ui->serialWidget, SIGNAL(LogSignal(QString)), this, SLOT(ShowMessage(QString)));
    connect(ui->serialWidget, SIGNAL(CleanStatsSignal()), this, SLOT(CleanData()));
    connect(&tickTimer, SIGNAL(timeout()), this, SLOT(tick()));
    connect(&handleTimer, SIGNAL(timeout()), this, SLOT(handle()));
    connect(&autoTimer, SIGNAL(timeout()), this, SLOT(sendFrame()));
    connect(SerialGetPt(), SIGNAL(readyRead()), this, SLOT(ReceiveSerialData()));

    comm_err err = comm_start();
    if(err == COMM_ERR_SUCCESS)
    {
        tickTimer.start(1);
        handleTimer.start(5);
//        autoTimer.start(100);
        for(int i = 4; i < 256; i++)
        {
            comm_register(i, tag_callback);
        }
        ShowMessage("协议启动成功");
    }
    else ShowMessage(QString("协议启动失败 错误码:%1").arg(err));
}

/**
 * @brief Destroy the Main Window:: Main Window object
 * 
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief 发送数据帧
 *
 */
void MainWindow::sendFrame()
{
    static comm_uint32 count = 0;
    if(SerialGetPt()->isOpen())
    {
        if(ui->tagLedit->text().toInt() == COMM_TAG_ACK)
        {
            ShowMessage("TAG输入错误");
            return;
        }
        comm_tlv_t tlv;
        tlv.tag = ui->tagLedit->text().toInt();
        QByteArray dat;
        if(ui->hexCkbox->isChecked())
        {
            QString str = ui->valueLedit->text();
            if(str.contains(" "))
            {
                str.replace(QString(" "),QString(""));
            }
            dat = HexStringToQByteArray(str);
        }
        else
        {
            dat = ui->valueLedit->text().toLatin1();
        }
        tlv.len = dat.length();
        tlv.value = (comm_uint8*)dat.data();
        count++;
        if(tlv.tag == 4)
            comm_send(tlv, COMM_FALSE, COMM_FALSE);
        else if(tlv.tag == 5)
            comm_send(tlv, COMM_FALSE, COMM_TRUE);
        else if(tlv.tag == 8)
            comm_send(tlv, COMM_TRUE, COMM_FALSE);
        else
            comm_send(tlv, COMM_TRUE, COMM_TRUE);
    }
    else
    {
        ShowMessage("请先打开串口");
    }
}

/**
 * @brief 清除数据
 *
 */
void MainWindow::CleanData()
{
    ui->commTedit->clear();
    ui->dataTxTedit->clear();
    ui->dataRxTedit->clear();
}

/**
 * @brief 节拍
 *
 */
void MainWindow::tick()
{
    comm_tick(1);
}

/**
 * @brief 处理
 *
 */
void MainWindow::handle()
{
//    fifo_mutex.lock();
    comm_handle();
//    fifo_mutex.unlock();
}

/**
 * @brief 接收串口数据
 *
 */
void MainWindow::ReceiveSerialData()
{
//    fifo_mutex.lock();
    QByteArray dat = SerialReadData();
    comm_getBuf((comm_uint8*)dat.data(), dat.length());
    ui->dataRxTedit->append(ByteArrayToHexString(dat));
//    fifo_mutex.unlock();
}

/**
 * @brief 协议字节流输出
 *
 * @param buf 数据地址
 * @param len 数据长度
 */
comm_err comm_putBuf(comm_uint8* buf, comm_uint32 len)
{
    if(SerialGetPt()->isOpen())
    {
        thispt->ui->dataTxTedit->append(ByteArrayToHexString(QByteArray((char*)buf, len)));
        if(SerialGetPt()->write((char*)buf, len) != -1)
            return COMM_ERR_SUCCESS;
        else
            return COMM_ERR_UNKNOW;
    }
    return COMM_ERR_SUCCESS;
}

/**
 * @brief 回调函数
 *
 */
static void tag_callback(uint16_t len, uint8_t* value)
{
    thispt->ui->commTedit->append(QByteArray((char*)value, len));
}

/**
 * @brief 
 * 
 * @param Message 
 */
void MainWindow::ShowMessage(QString Message)
{
    ui->statusbar->showMessage(Message, 1500);
}

/**
 * @brief QByteArray转QString
 *
 * @param ascii
 * @return QString
 */
static QString ByteArrayToHexString(QByteArray ascii)
{
    QString ret;
    for(int i = 0; i < ascii.count(); i++)
    {
        ret.append(QString("%1 ").arg((uchar)ascii.at(i), 2, 16, (QChar)'0'));
    }
    return ret.toUpper();
}

/**
 * @brief Char转Hex
 *
 * @param ch
 * @return char
 */
static char ConvertCharToHex(char ch)
{
    /*
        0x30等于十进制的48，48也是0的ASCII值，，
        1-9的ASCII值是49-57，所以某一个值－0x30，，
        就是将字符0-9转换为0-9
    */
    if((ch >= '0') && (ch <= '9'))
         return ch-0x30;
     else if((ch >= 'A') && (ch <= 'F'))
         return ch-'A'+10;
     else if((ch >= 'a') && (ch <= 'f'))
         return ch-'a'+10;
     else return -1;
}

/**
 * @brief Hex字符串转QByteArray
 *
 * @param str
 * @return QByteArray
 */
static QByteArray HexStringToQByteArray(QString str)
{
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    QByteArray byteData;
    byteData.resize(len/2);
    char lstr, hstr;
    for(int i = 0; i < len; i++)
    {
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = ConvertCharToHex(hstr);
        lowhexdata = ConvertCharToHex(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = (hexdata << 4) + lowhexdata;
        byteData[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    byteData.resize(hexdatalen);
    return byteData;
}
