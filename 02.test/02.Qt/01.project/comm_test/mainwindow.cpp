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
#include "../../../../01.comm/comm.h"

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
    connect(ui->serialWidget, SIGNAL(LogSignal(QString)), this, SLOT(ShowMessage(QString)));
    connect(ui->serialWidget, SIGNAL(CleanStatsSignal()), this, SLOT(CleanData()));
    connect(&tickTimer, SIGNAL(timeout()), this, SLOT(tick()));
    connect(&handleTimer, SIGNAL(timeout()), this, SLOT(handle()));
    connect(SerialGetPt(), SIGNAL(readyRead()), this, SLOT(ReceiveSerialData()));

    comm_err err = comm_start();
    if(err == COMM_ERR_SUCCESS)
    {
        tickTimer.start(1);
        handleTimer.start(20);
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
    comm_handle();
}

/**
 * @brief 接收串口数据
 *
 */
void MainWindow::ReceiveSerialData()
{
    QByteArray dat = SerialReadData();
    comm_getBuf((comm_uint8*)dat.data(), dat.length());
}

/**
 * @brief 协议字节流输出
 *
 * @param buf 数据地址
 * @param len 数据长度
 */
comm_err comm_putBuf(comm_uint8* buf, comm_uint32 len)
{
    if(SerialGetPt()->write((char*)buf, len) != -1)
        return COMM_ERR_SUCCESS;
    else
        return COMM_ERR_UNKNOW;
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
 * @brief 清除数据
 * 
 */
void MainWindow::CleanData()
{

}
