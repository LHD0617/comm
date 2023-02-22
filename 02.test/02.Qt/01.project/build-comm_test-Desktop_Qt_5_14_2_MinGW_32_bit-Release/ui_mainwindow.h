/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "serialtool.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QGroupBox *commGbox;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *commTedit;
    QGroupBox *dataGbox;
    QGridLayout *gridLayout;
    QLabel *dataTxLab;
    QLabel *dataRxLab;
    QTextEdit *dataTxTedit;
    QTextEdit *dataRxTedit;
    QGroupBox *sendGbox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *tagLab;
    QLineEdit *tagLedit;
    QLabel *valueLab;
    QLineEdit *valueLedit;
    QCheckBox *hexCkbox;
    QPushButton *sendPbtn;
    SerialTool *serialWidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(974, 708);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        commGbox = new QGroupBox(splitter);
        commGbox->setObjectName(QString::fromUtf8("commGbox"));
        verticalLayout_2 = new QVBoxLayout(commGbox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        commTedit = new QTextEdit(commGbox);
        commTedit->setObjectName(QString::fromUtf8("commTedit"));
        commTedit->setTextInteractionFlags(Qt::TextSelectableByMouse);

        verticalLayout_2->addWidget(commTedit);

        splitter->addWidget(commGbox);
        dataGbox = new QGroupBox(splitter);
        dataGbox->setObjectName(QString::fromUtf8("dataGbox"));
        gridLayout = new QGridLayout(dataGbox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        dataTxLab = new QLabel(dataGbox);
        dataTxLab->setObjectName(QString::fromUtf8("dataTxLab"));

        gridLayout->addWidget(dataTxLab, 0, 0, 1, 1);

        dataRxLab = new QLabel(dataGbox);
        dataRxLab->setObjectName(QString::fromUtf8("dataRxLab"));

        gridLayout->addWidget(dataRxLab, 0, 1, 1, 1);

        dataTxTedit = new QTextEdit(dataGbox);
        dataTxTedit->setObjectName(QString::fromUtf8("dataTxTedit"));
        dataTxTedit->setTextInteractionFlags(Qt::TextSelectableByMouse);

        gridLayout->addWidget(dataTxTedit, 1, 0, 1, 1);

        dataRxTedit = new QTextEdit(dataGbox);
        dataRxTedit->setObjectName(QString::fromUtf8("dataRxTedit"));
        dataRxTedit->setTextInteractionFlags(Qt::TextSelectableByMouse);

        gridLayout->addWidget(dataRxTedit, 1, 1, 1, 1);

        splitter->addWidget(dataGbox);

        verticalLayout->addWidget(splitter);

        sendGbox = new QGroupBox(centralwidget);
        sendGbox->setObjectName(QString::fromUtf8("sendGbox"));
        horizontalLayout_2 = new QHBoxLayout(sendGbox);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        tagLab = new QLabel(sendGbox);
        tagLab->setObjectName(QString::fromUtf8("tagLab"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tagLab->sizePolicy().hasHeightForWidth());
        tagLab->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(tagLab);

        tagLedit = new QLineEdit(sendGbox);
        tagLedit->setObjectName(QString::fromUtf8("tagLedit"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tagLedit->sizePolicy().hasHeightForWidth());
        tagLedit->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(tagLedit);

        valueLab = new QLabel(sendGbox);
        valueLab->setObjectName(QString::fromUtf8("valueLab"));
        sizePolicy.setHeightForWidth(valueLab->sizePolicy().hasHeightForWidth());
        valueLab->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(valueLab);

        valueLedit = new QLineEdit(sendGbox);
        valueLedit->setObjectName(QString::fromUtf8("valueLedit"));

        horizontalLayout_2->addWidget(valueLedit);

        hexCkbox = new QCheckBox(sendGbox);
        hexCkbox->setObjectName(QString::fromUtf8("hexCkbox"));

        horizontalLayout_2->addWidget(hexCkbox);

        sendPbtn = new QPushButton(sendGbox);
        sendPbtn->setObjectName(QString::fromUtf8("sendPbtn"));

        horizontalLayout_2->addWidget(sendPbtn);


        verticalLayout->addWidget(sendGbox);


        horizontalLayout->addLayout(verticalLayout);

        serialWidget = new SerialTool(centralwidget);
        serialWidget->setObjectName(QString::fromUtf8("serialWidget"));
        serialWidget->setMinimumSize(QSize(200, 0));
        serialWidget->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(serialWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "comm_test", nullptr));
        commGbox->setTitle(QCoreApplication::translate("MainWindow", "\345\215\217\350\256\256\346\225\260\346\215\256\347\252\227\345\217\243", nullptr));
        commTedit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        dataGbox->setTitle(QCoreApplication::translate("MainWindow", "\345\216\237\345\247\213\346\225\260\346\215\256\347\252\227\345\217\243", nullptr));
        dataTxLab->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\346\225\260\346\215\256\357\274\232", nullptr));
        dataRxLab->setText(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266\346\225\260\346\215\256\357\274\232", nullptr));
        sendGbox->setTitle(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\347\252\227\345\217\243", nullptr));
        tagLab->setText(QCoreApplication::translate("MainWindow", "TAG\357\274\232", nullptr));
        valueLab->setText(QCoreApplication::translate("MainWindow", "VALUE\357\274\232", nullptr));
        hexCkbox->setText(QCoreApplication::translate("MainWindow", "\345\215\201\345\205\255\350\277\233\345\210\266\345\217\221\351\200\201", nullptr));
        sendPbtn->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
