/**
 * @file main.cpp
 * @author 满心欢喜
 * @brief 主函数
 * @version 0.1
 * @date 2023-02-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* @include */
#include "mainwindow.h"
#include <QApplication>

/**
 * @brief 主函数
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
