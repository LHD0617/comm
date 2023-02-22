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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/* @include */
#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;
    QTimer tickTimer;
    QTimer handleTimer;

public slots:
    void tick();
    void handle();
    void sendFrame();
    void ReceiveSerialData();
    void ShowMessage(QString Message);
    void CleanData(void);
};
#endif // MAINWINDOW_H
