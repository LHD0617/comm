/**
 * @file serialtool.h
 * @author 满心欢喜
 * @brief 串口工具
 * @version 0.1
 * @date 2023-01-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SERIALTOOL_H
#define SERIALTOOL_H

/* @include */
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QSerialPortInfo>
#include <QSerialPort>

namespace Ui {
class SerialTool;
}

class SerialTool : public QWidget
{
    Q_OBJECT

public:
    SerialTool(QWidget *parent = nullptr);
    ~SerialTool();

    QLabel* SerialStateLab;

private:
    Ui::SerialTool *ui;
    QStringList PortList;
    QSerialPort Ser;
    QTimer RefreshPortTimer;

private slots:
    void RefreshPort();
    void SwitchPort();
    void SendCleanStatsSignal();
    void WriteConfig(int index);
    void ReadConfig();

signals:
    void LogSignal(QString Message);
    void CleanStatsSignal();
};

/* @Function declaration */
QByteArray SerialReadData();
bool SerialSendData(const char* pdata, uint32_t len);
QSerialPort* SerialGetPt();
bool SerialGetState();

#endif // SERIALTOOL_H
