/********************************************************************************
** Form generated from reading UI file 'serialtool.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALTOOL_H
#define UI_SERIALTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SerialTool
{
public:
    QGridLayout *gridLayout;
    QLabel *PortLab;
    QComboBox *PortCbox;
    QLabel *BaudLab;
    QComboBox *BaudCbox;
    QLabel *DataBitLab;
    QComboBox *DataBitCbox;
    QLabel *CheckBitLab;
    QComboBox *CheckBitCbox;
    QLabel *StopBitLab;
    QComboBox *StopBitCbox;
    QPushButton *SwitchPortPbtn;
    QPushButton *CleanStatsPbtn;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SerialTool)
    {
        if (SerialTool->objectName().isEmpty())
            SerialTool->setObjectName(QString::fromUtf8("SerialTool"));
        SerialTool->resize(200, 600);
        gridLayout = new QGridLayout(SerialTool);
        gridLayout->setSpacing(20);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        PortLab = new QLabel(SerialTool);
        PortLab->setObjectName(QString::fromUtf8("PortLab"));

        gridLayout->addWidget(PortLab, 0, 0, 1, 1);

        PortCbox = new QComboBox(SerialTool);
        PortCbox->setObjectName(QString::fromUtf8("PortCbox"));

        gridLayout->addWidget(PortCbox, 0, 1, 1, 1);

        BaudLab = new QLabel(SerialTool);
        BaudLab->setObjectName(QString::fromUtf8("BaudLab"));

        gridLayout->addWidget(BaudLab, 1, 0, 1, 1);

        BaudCbox = new QComboBox(SerialTool);
        BaudCbox->addItem(QString());
        BaudCbox->addItem(QString());
        BaudCbox->addItem(QString());
        BaudCbox->addItem(QString());
        BaudCbox->addItem(QString());
        BaudCbox->addItem(QString());
        BaudCbox->addItem(QString());
        BaudCbox->addItem(QString());
        BaudCbox->addItem(QString());
        BaudCbox->addItem(QString());
        BaudCbox->addItem(QString());
        BaudCbox->addItem(QString());
        BaudCbox->addItem(QString());
        BaudCbox->addItem(QString());
        BaudCbox->addItem(QString());
        BaudCbox->addItem(QString());
        BaudCbox->addItem(QString());
        BaudCbox->setObjectName(QString::fromUtf8("BaudCbox"));

        gridLayout->addWidget(BaudCbox, 1, 1, 1, 1);

        DataBitLab = new QLabel(SerialTool);
        DataBitLab->setObjectName(QString::fromUtf8("DataBitLab"));

        gridLayout->addWidget(DataBitLab, 2, 0, 1, 1);

        DataBitCbox = new QComboBox(SerialTool);
        DataBitCbox->addItem(QString());
        DataBitCbox->addItem(QString());
        DataBitCbox->addItem(QString());
        DataBitCbox->addItem(QString());
        DataBitCbox->setObjectName(QString::fromUtf8("DataBitCbox"));

        gridLayout->addWidget(DataBitCbox, 2, 1, 1, 1);

        CheckBitLab = new QLabel(SerialTool);
        CheckBitLab->setObjectName(QString::fromUtf8("CheckBitLab"));

        gridLayout->addWidget(CheckBitLab, 3, 0, 1, 1);

        CheckBitCbox = new QComboBox(SerialTool);
        CheckBitCbox->addItem(QString());
        CheckBitCbox->addItem(QString());
        CheckBitCbox->addItem(QString());
        CheckBitCbox->setObjectName(QString::fromUtf8("CheckBitCbox"));

        gridLayout->addWidget(CheckBitCbox, 3, 1, 1, 1);

        StopBitLab = new QLabel(SerialTool);
        StopBitLab->setObjectName(QString::fromUtf8("StopBitLab"));

        gridLayout->addWidget(StopBitLab, 4, 0, 1, 1);

        StopBitCbox = new QComboBox(SerialTool);
        StopBitCbox->addItem(QString());
        StopBitCbox->addItem(QString());
        StopBitCbox->addItem(QString());
        StopBitCbox->setObjectName(QString::fromUtf8("StopBitCbox"));

        gridLayout->addWidget(StopBitCbox, 4, 1, 1, 1);

        SwitchPortPbtn = new QPushButton(SerialTool);
        SwitchPortPbtn->setObjectName(QString::fromUtf8("SwitchPortPbtn"));

        gridLayout->addWidget(SwitchPortPbtn, 5, 0, 1, 2);

        CleanStatsPbtn = new QPushButton(SerialTool);
        CleanStatsPbtn->setObjectName(QString::fromUtf8("CleanStatsPbtn"));

        gridLayout->addWidget(CleanStatsPbtn, 6, 0, 1, 2);

        verticalSpacer = new QSpacerItem(179, 293, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 7, 0, 1, 2);


        retranslateUi(SerialTool);

        QMetaObject::connectSlotsByName(SerialTool);
    } // setupUi

    void retranslateUi(QWidget *SerialTool)
    {
        SerialTool->setWindowTitle(QCoreApplication::translate("SerialTool", "Form", nullptr));
        PortLab->setText(QCoreApplication::translate("SerialTool", "\347\253\257  \345\217\243\357\274\232", nullptr));
        BaudLab->setText(QCoreApplication::translate("SerialTool", "\346\263\242\347\211\271\347\216\207\357\274\232", nullptr));
        BaudCbox->setItemText(0, QCoreApplication::translate("SerialTool", "9600", nullptr));
        BaudCbox->setItemText(1, QCoreApplication::translate("SerialTool", "19200", nullptr));
        BaudCbox->setItemText(2, QCoreApplication::translate("SerialTool", "38400", nullptr));
        BaudCbox->setItemText(3, QCoreApplication::translate("SerialTool", "57600", nullptr));
        BaudCbox->setItemText(4, QCoreApplication::translate("SerialTool", "115200", nullptr));
        BaudCbox->setItemText(5, QCoreApplication::translate("SerialTool", "460800", nullptr));
        BaudCbox->setItemText(6, QCoreApplication::translate("SerialTool", "500000", nullptr));
        BaudCbox->setItemText(7, QCoreApplication::translate("SerialTool", "576000", nullptr));
        BaudCbox->setItemText(8, QCoreApplication::translate("SerialTool", "921600", nullptr));
        BaudCbox->setItemText(9, QCoreApplication::translate("SerialTool", "1000000", nullptr));
        BaudCbox->setItemText(10, QCoreApplication::translate("SerialTool", "1152000", nullptr));
        BaudCbox->setItemText(11, QCoreApplication::translate("SerialTool", "1500000", nullptr));
        BaudCbox->setItemText(12, QCoreApplication::translate("SerialTool", "2000000", nullptr));
        BaudCbox->setItemText(13, QCoreApplication::translate("SerialTool", "2500000", nullptr));
        BaudCbox->setItemText(14, QCoreApplication::translate("SerialTool", "3000000", nullptr));
        BaudCbox->setItemText(15, QCoreApplication::translate("SerialTool", "3500000", nullptr));
        BaudCbox->setItemText(16, QCoreApplication::translate("SerialTool", "4000000", nullptr));

        DataBitLab->setText(QCoreApplication::translate("SerialTool", "\346\225\260\346\215\256\344\275\215\357\274\232", nullptr));
        DataBitCbox->setItemText(0, QCoreApplication::translate("SerialTool", "8", nullptr));
        DataBitCbox->setItemText(1, QCoreApplication::translate("SerialTool", "7", nullptr));
        DataBitCbox->setItemText(2, QCoreApplication::translate("SerialTool", "6", nullptr));
        DataBitCbox->setItemText(3, QCoreApplication::translate("SerialTool", "5", nullptr));

        CheckBitLab->setText(QCoreApplication::translate("SerialTool", "\346\240\241\351\252\214\344\275\215\357\274\232", nullptr));
        CheckBitCbox->setItemText(0, QCoreApplication::translate("SerialTool", "\346\227\240\346\240\241\351\252\214", nullptr));
        CheckBitCbox->setItemText(1, QCoreApplication::translate("SerialTool", "\345\201\266\346\240\241\351\252\214", nullptr));
        CheckBitCbox->setItemText(2, QCoreApplication::translate("SerialTool", "\345\245\207\346\240\241\351\252\214", nullptr));

        StopBitLab->setText(QCoreApplication::translate("SerialTool", "\345\201\234\346\255\242\344\275\215\357\274\232", nullptr));
        StopBitCbox->setItemText(0, QCoreApplication::translate("SerialTool", "1", nullptr));
        StopBitCbox->setItemText(1, QCoreApplication::translate("SerialTool", "2", nullptr));
        StopBitCbox->setItemText(2, QCoreApplication::translate("SerialTool", "1.5", nullptr));

        SwitchPortPbtn->setText(QCoreApplication::translate("SerialTool", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        CleanStatsPbtn->setText(QCoreApplication::translate("SerialTool", "\346\270\205\347\251\272\347\273\237\350\256\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SerialTool: public Ui_SerialTool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALTOOL_H
