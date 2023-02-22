/**
 * @file serialtool.cpp
 * @author 满心欢喜
 * @brief 串口工具
 * @version 0.1
 * @date 2023-01-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "serialtool.h"
#include "ui_serialtool.h"
#include "systemconfig.h"

/* 窗口对象指针 */
static QSerialPort* SerialPt;

/* 串口打开状态 */
static bool SwitchPortFlag;

/**
 * @brief Construct a new Serial Tool:: Serial Tool object
 * 
 * @param parent 
 */
SerialTool::SerialTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialTool)
{
    SerialPt = &Ser;

    SwitchPortFlag = false;

    ui->setupUi(this);
    SerialStateLab = new QLabel("串口状态：未连接");
    ReadConfig();

    connect(ui->SwitchPortPbtn, SIGNAL(clicked()), this, SLOT(SwitchPort()));
    connect(ui->CleanStatsPbtn, SIGNAL(clicked()), this, SLOT(SendCleanStatsSignal()));
    connect(&RefreshPortTimer, SIGNAL(timeout()), this, SLOT(RefreshPort()));

    connect(ui->BaudCbox, SIGNAL(currentIndexChanged(int)), this, SLOT(WriteConfig(int)));
    connect(ui->DataBitCbox, SIGNAL(currentIndexChanged(int)), this, SLOT(WriteConfig(int)));
    connect(ui->CheckBitCbox, SIGNAL(currentIndexChanged(int)), this, SLOT(WriteConfig(int)));
    connect(ui->StopBitCbox, SIGNAL(currentIndexChanged(int)), this, SLOT(WriteConfig(int)));

    RefreshPortTimer.start(200);
}

/**
 * @brief Destroy the Serial Tool:: Serial Tool object
 * 
 */
SerialTool::~SerialTool()
{
    delete ui;
}

/**
 * @brief 刷新串口列表
 * 
 */
void SerialTool::RefreshPort()
{
    QStringList TempPortList;
    if(!SwitchPortFlag)
    {
        foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            TempPortList << info.portName();
        }
        if(TempPortList != PortList)
        {
            PortList.clear();
            PortList = TempPortList;
            ui->PortCbox->clear();
            ui->PortCbox->addItems(PortList);
        }
    }
    else
    {
        foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            TempPortList << info.portName();
        }
        if(!TempPortList.contains(ui->PortCbox->currentText()))
        {
            SwitchPort();
        }
    }
}

/**
 * @brief 串口开关
 * 
 */
void SerialTool::SwitchPort()
{
    if(!SwitchPortFlag)
    {
        if(ui->PortCbox->count() > 0)
        {
            Ser.setPortName(ui->PortCbox->currentText());
            Ser.setBaudRate(ui->BaudCbox->currentText().toInt());
            Ser.setDataBits((QSerialPort::DataBits)ui->DataBitCbox->currentText().toInt());

            uint8_t CheckBit = ui->CheckBitCbox->currentIndex();
            if(!CheckBit)
            {
                Ser.setParity((QSerialPort::NoParity));
            }
            else
            {
                Ser.setParity((QSerialPort::Parity)(CheckBit + 1));
            }
            Ser.setStopBits((QSerialPort::StopBits)ui->StopBitCbox->currentIndex());
            if(Ser.open(QIODevice::ReadWrite))
            {
                emit LogSignal(ui->PortCbox->currentText() + "打开成功");
                SwitchPortFlag = true;
                ui->SwitchPortPbtn->setText("关闭串口");
                SerialStateLab->setText("串口状态：" + ui->PortCbox->currentText() + "已连接");
                ui->PortCbox->setEnabled(false);
                ui->BaudCbox->setEnabled(false);
                ui->DataBitCbox->setEnabled(false);
                ui->CheckBitCbox->setEnabled(false);
                ui->StopBitCbox->setEnabled(false);
                Ser.clear();
            }
            else
            {
                emit LogSignal(ui->PortCbox->currentText() + "打开失败");
            }
        }
        else
        {
            emit LogSignal("未搜索到可用串口");
        }
    }
    else
    {
        SwitchPortFlag = false;
        ui->SwitchPortPbtn->setText("打开串口");
        SerialStateLab->setText("串口状态：未连接");
        ui->PortCbox->setEnabled(true);
        ui->BaudCbox->setEnabled(true);
        ui->DataBitCbox->setEnabled(true);
        ui->CheckBitCbox->setEnabled(true);
        ui->StopBitCbox->setEnabled(true);
        Ser.close();
        emit LogSignal(ui->PortCbox->currentText() + "已关闭");
    }
}

/**
 * @brief 写入配置信息
 *
 */
void SerialTool::WriteConfig(int index)
{
    SystemConfigWrite("Serial", "baud", QString::number(ui->BaudCbox->currentIndex()));
    SystemConfigWrite("Serial", "data", QString::number(ui->DataBitCbox->currentIndex()));
    SystemConfigWrite("Serial", "check", QString::number(ui->CheckBitCbox->currentIndex()));
    SystemConfigWrite("Serial", "stop", QString::number(ui->StopBitCbox->currentIndex()));
}

/**
 * @brief 读取配置信息
 *
 */
void SerialTool::ReadConfig()
{
    ui->BaudCbox->setCurrentIndex(SystemConfigRead("Serial", "baud").toInt());
    ui->DataBitCbox->setCurrentIndex(SystemConfigRead("Serial", "data").toInt());
    ui->CheckBitCbox->setCurrentIndex(SystemConfigRead("Serial", "check").toInt());
    ui->StopBitCbox->setCurrentIndex(SystemConfigRead("Serial", "stop").toInt());
}

/**
 * @brief 发送清空统计信号
 * 
 */
void SerialTool::SendCleanStatsSignal()
{
    emit CleanStatsSignal();
}

/**
 * @brief 获取串口对象指针
 * 
 * @return QSerialPort* 
 */
QSerialPort* SerialGetPt()
{
    return SerialPt;
}

/**
 * @brief 获取串口连接状态
 * 
 * @return true 
 * @return false 
 */
bool SerialGetState()
{
    return SwitchPortFlag;
}

/**
 * @brief 串口接收数据
 * 
 * @return QByteArray 
 */
QByteArray SerialReadData()
{
    return SerialPt->readAll();
}

/**
 * @brief 串口发送数据
 * 
 * @param pdata 
 * @param len 
 */
bool SerialSendData(const char* pdata, uint32_t len)
{
    if(SerialPt->write(pdata, len) != -1)
        return true;
    else
        return false;
}
