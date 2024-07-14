/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *stockPriceLineEdit;
    QLineEdit *interestRateLineEdit;
    QLineEdit *volatilityLineEdit;
    QLineEdit *timeToMaturityLineEdit;
    QLineEdit *numSimulationsLineEdit;
    QPushButton *calculateButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *strikePriceLineEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stockPriceLineEdit = new QLineEdit(centralwidget);
        stockPriceLineEdit->setObjectName("stockPriceLineEdit");
        stockPriceLineEdit->setGeometry(QRect(0, 260, 113, 28));
        interestRateLineEdit = new QLineEdit(centralwidget);
        interestRateLineEdit->setObjectName("interestRateLineEdit");
        interestRateLineEdit->setGeometry(QRect(460, 260, 113, 28));
        volatilityLineEdit = new QLineEdit(centralwidget);
        volatilityLineEdit->setObjectName("volatilityLineEdit");
        volatilityLineEdit->setGeometry(QRect(640, 260, 113, 28));
        timeToMaturityLineEdit = new QLineEdit(centralwidget);
        timeToMaturityLineEdit->setObjectName("timeToMaturityLineEdit");
        timeToMaturityLineEdit->setGeometry(QRect(150, 260, 113, 28));
        numSimulationsLineEdit = new QLineEdit(centralwidget);
        numSimulationsLineEdit->setObjectName("numSimulationsLineEdit");
        numSimulationsLineEdit->setGeometry(QRect(360, 380, 113, 28));
        calculateButton = new QPushButton(centralwidget);
        calculateButton->setObjectName("calculateButton");
        calculateButton->setGeometry(QRect(380, 480, 83, 29));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 220, 111, 31));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 210, 141, 41));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(290, 210, 101, 51));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(410, 210, 211, 41));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(620, 220, 211, 31));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(330, 320, 191, 51));
        strikePriceLineEdit = new QLineEdit(centralwidget);
        strikePriceLineEdit->setObjectName("strikePriceLineEdit");
        strikePriceLineEdit->setGeometry(QRect(290, 260, 113, 28));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        stockPriceLineEdit->setText(QString());
        interestRateLineEdit->setText(QString());
        volatilityLineEdit->setText(QString());
        timeToMaturityLineEdit->setText(QString());
        numSimulationsLineEdit->setText(QString());
        calculateButton->setText(QCoreApplication::translate("MainWindow", "Calculate", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Stock Price (S0):", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Time to Maturity (T):", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Strike Price (K):", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Risk free rate (R) [in decimals]:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Volatility (\317\203) [in decimals]:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Number of Simulations:", nullptr));
        strikePriceLineEdit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
