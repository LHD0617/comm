/**
 * @file systemconfig.cpp
 * @author 满心欢喜
 * @brief 系统配置
 * @version 0.1
 * @date 2023-01-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* @include */
#include "systemconfig.h"
#include <QSettings>

static QSettings config("SystemConfig.ini", QSettings::IniFormat);

/**
 * @brief 写入配置信息
 * 
 * @param group 
 * @param label 
 * @param value 
 */
void SystemConfigWrite(QString group, QString label, QString value)
{
    config.setIniCodec("UTF8");
    config.setValue(QString("%1/%2").arg(group).arg(label), value);
}

/**
 * @brief 读取配置信息
 * 
 * @param group 
 * @param label 
 * @return QString 
 */
QString SystemConfigRead(QString group, QString label)
{
    QSettings config("SystemConfig.ini", QSettings::IniFormat);
    config.setIniCodec("UTF8");
    config.beginGroup(group);
    QString value = config.value(label).toString();
    config.endGroup();
    return value;
}

