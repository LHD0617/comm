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
    QVBoxLayout *verticalLayout_3;
    QTextEdit *dataTedit;
    QGroupBox *groupBox_3;
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
        verticalLayout_3 = new QVBoxLayout(dataGbox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        dataTedit = new QTextEdit(dataGbox);
        dataTedit->setObjectName(QString::fromUtf8("dataTedit"));
        dataTedit->setTextInteractionFlags(Qt::TextSelectableByMouse);

        verticalLayout_3->addWidget(dataTedit);

        groupBox_3 = new QGroupBox(dataGbox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        tagLab = new QLabel(groupBox_3);
        tagLab->setObjectName(QString::fromUtf8("tagLab"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tagLab->sizePolicy().hasHeightForWidth());
        tagLab->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(tagLab);

        tagLedit = new QLineEdit(groupBox_3);
        tagLedit->setObjectName(QString::fromUtf8("tagLedit"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tagLedit->sizePolicy().hasHeightForWidth());
        tagLedit->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(tagLedit);

        valueLab = new QLabel(groupBox_3);
        valueLab->setObjectName(QString::fromUtf8("valueLab"));
        sizePolicy.setHeightForWidth(valueLab->sizePolicy().hasHeightForWidth());
        valueLab->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(valueLab);

        valueLedit = new QLineEdit(groupBox_3);
        valueLedit->setObjectName(QString::fromUtf8("valueLedit"));

        horizontalLayout_2->addWidget(valueLedit);

        hexCkbox = new QCheckBox(groupBox_3);
        hexCkbox->setObjectName(QString::fromUtf8("hexCkbox"));

        horizontalLayout_2->addWidget(hexCkbox);

        sendPbtn = new QPushButton(groupBox_3);
        sendPbtn->setObjectName(QString::fromUtf8("sendPbtn"));

        horizontalLayout_2->addWidget(sendPbtn);


        verticalLayout_3->addWidget(groupBox_3);

        splitter->addWidget(dataGbox);

        verticalLayout->addWidget(splitter);


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
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\347\252\227\345\217\243", nullptr));
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
