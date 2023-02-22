/**
 * @file systemconfig.h
 * @author 满心欢喜
 * @brief 系统配置
 * @version 0.1
 * @date 2023-01-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SYSTEMCONFIG_H
#define SYSTEMCONFIG_H

/* @include */
#include <QString>

/* @Function declaration */
void SystemConfigWrite(QString group, QString label, QString value);
QString SystemConfigRead(QString group, QString label);

#endif // SYSTEMCONFIG_H
