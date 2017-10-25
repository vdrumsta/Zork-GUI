/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *northButton;
    QPushButton *westButton;
    QPushButton *eastButton;
    QPushButton *southButton;
    QLabel *roomDescription;
    QGraphicsView *roomGraphicsView;
    QGraphicsView *graphicsView;
    QPushButton *take;
    QLabel *playerInventory;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(611, 596);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        northButton = new QPushButton(centralWidget);
        northButton->setObjectName(QStringLiteral("northButton"));
        northButton->setGeometry(QRect(60, 140, 75, 23));
        westButton = new QPushButton(centralWidget);
        westButton->setObjectName(QStringLiteral("westButton"));
        westButton->setGeometry(QRect(10, 180, 75, 23));
        eastButton = new QPushButton(centralWidget);
        eastButton->setObjectName(QStringLiteral("eastButton"));
        eastButton->setGeometry(QRect(120, 180, 75, 23));
        southButton = new QPushButton(centralWidget);
        southButton->setObjectName(QStringLiteral("southButton"));
        southButton->setGeometry(QRect(60, 220, 75, 23));
        roomDescription = new QLabel(centralWidget);
        roomDescription->setObjectName(QStringLiteral("roomDescription"));
        roomDescription->setGeometry(QRect(20, 500, 191, 51));
        roomGraphicsView = new QGraphicsView(centralWidget);
        roomGraphicsView->setObjectName(QStringLiteral("roomGraphicsView"));
        roomGraphicsView->setGeometry(QRect(220, 130, 391, 361));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 611, 131));
        take = new QPushButton(centralWidget);
        take->setObjectName(QStringLiteral("take"));
        take->setGeometry(QRect(10, 280, 75, 23));
        playerInventory = new QLabel(centralWidget);
        playerInventory->setObjectName(QStringLiteral("playerInventory"));
        playerInventory->setGeometry(QRect(100, 280, 101, 101));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 611, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        northButton->setText(QApplication::translate("MainWindow", "North", 0));
        westButton->setText(QApplication::translate("MainWindow", "West", 0));
        eastButton->setText(QApplication::translate("MainWindow", "East", 0));
        southButton->setText(QApplication::translate("MainWindow", "South", 0));
        roomDescription->setText(QApplication::translate("MainWindow", "room", 0));
        take->setText(QApplication::translate("MainWindow", "take Item", 0));
        playerInventory->setText(QApplication::translate("MainWindow", "player inventory", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
