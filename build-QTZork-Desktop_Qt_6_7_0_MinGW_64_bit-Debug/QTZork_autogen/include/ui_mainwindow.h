/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
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
    QLineEdit *lineEdit;
    QLineEdit *outputLineEdit;
    QPushButton *North;
    QPushButton *South;
    QPushButton *West;
    QPushButton *East;
    QLabel *imageHolder;
    QPushButton *showMenu;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1920, 1080);
        QFont font;
        font.setFamilies({QString::fromUtf8("8514oem")});
        font.setPointSize(9);
        font.setBold(false);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(200, 260, 481, 61));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Albra Text")});
        font1.setPointSize(14);
        font1.setBold(true);
        lineEdit->setFont(font1);
        lineEdit->setAcceptDrops(false);
        outputLineEdit = new QLineEdit(centralwidget);
        outputLineEdit->setObjectName("outputLineEdit");
        outputLineEdit->setGeometry(QRect(200, 340, 481, 241));
        sizePolicy.setHeightForWidth(outputLineEdit->sizePolicy().hasHeightForWidth());
        outputLineEdit->setSizePolicy(sizePolicy);
        outputLineEdit->setFont(font1);
        outputLineEdit->setAcceptDrops(false);
        North = new QPushButton(centralwidget);
        North->setObjectName("North");
        North->setGeometry(QRect(1290, 700, 83, 29));
        sizePolicy.setHeightForWidth(North->sizePolicy().hasHeightForWidth());
        North->setSizePolicy(sizePolicy);
        North->setFont(font1);
        North->setAcceptDrops(false);
        South = new QPushButton(centralwidget);
        South->setObjectName("South");
        South->setGeometry(QRect(1290, 760, 83, 29));
        sizePolicy.setHeightForWidth(South->sizePolicy().hasHeightForWidth());
        South->setSizePolicy(sizePolicy);
        South->setFont(font1);
        South->setAcceptDrops(false);
        West = new QPushButton(centralwidget);
        West->setObjectName("West");
        West->setGeometry(QRect(1200, 730, 83, 29));
        sizePolicy.setHeightForWidth(West->sizePolicy().hasHeightForWidth());
        West->setSizePolicy(sizePolicy);
        West->setFont(font1);
        West->setAcceptDrops(false);
        East = new QPushButton(centralwidget);
        East->setObjectName("East");
        East->setGeometry(QRect(1370, 730, 83, 29));
        sizePolicy.setHeightForWidth(East->sizePolicy().hasHeightForWidth());
        East->setSizePolicy(sizePolicy);
        East->setFont(font1);
        East->setAcceptDrops(false);
        imageHolder = new QLabel(centralwidget);
        imageHolder->setObjectName("imageHolder");
        imageHolder->setGeometry(QRect(-10, 0, 1551, 821));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(imageHolder->sizePolicy().hasHeightForWidth());
        imageHolder->setSizePolicy(sizePolicy1);
        imageHolder->setFont(font1);
        imageHolder->setAcceptDrops(false);
        showMenu = new QPushButton(centralwidget);
        showMenu->setObjectName("showMenu");
        showMenu->setGeometry(QRect(1430, 780, 83, 29));
        sizePolicy.setHeightForWidth(showMenu->sizePolicy().hasHeightForWidth());
        showMenu->setSizePolicy(sizePolicy);
        showMenu->setFont(font1);
        showMenu->setAcceptDrops(false);
        MainWindow->setCentralWidget(centralwidget);
        imageHolder->raise();
        lineEdit->raise();
        outputLineEdit->raise();
        North->raise();
        South->raise();
        West->raise();
        East->raise();
        showMenu->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1920, 25));
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
        North->setText(QCoreApplication::translate("MainWindow", "NORTH", nullptr));
        South->setText(QCoreApplication::translate("MainWindow", "SOUTH", nullptr));
        West->setText(QCoreApplication::translate("MainWindow", "WEST", nullptr));
        East->setText(QCoreApplication::translate("MainWindow", "EAST", nullptr));
        imageHolder->setText(QString());
        showMenu->setText(QCoreApplication::translate("MainWindow", "MENU", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
