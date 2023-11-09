/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *algorithmBox;
    QLCDNumber *lcdNumber;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QPushButton *setEndButton;
    QPushButton *clearButton;
    QPushButton *customButton;
    QPushButton *generateButton;
    QPushButton *pauseButton;
    QPushButton *startButton;
    QPushButton *setStartButton;
    QPushButton *guantletButton;
    QPushButton *resetButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(463, 309);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName("actionQuit");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setMaximumSize(QSize(85, 16777215));
        label->setLineWidth(1);
        label->setMargin(3);

        horizontalLayout->addWidget(label, 0, Qt::AlignTop);

        algorithmBox = new QComboBox(centralwidget);
        algorithmBox->addItem(QString());
        algorithmBox->addItem(QString());
        algorithmBox->addItem(QString());
        algorithmBox->setObjectName("algorithmBox");
        algorithmBox->setMaximumSize(QSize(150, 16777215));

        horizontalLayout->addWidget(algorithmBox, 0, Qt::AlignTop);

        lcdNumber = new QLCDNumber(centralwidget);
        lcdNumber->setObjectName("lcdNumber");

        horizontalLayout->addWidget(lcdNumber, 0, Qt::AlignRight|Qt::AlignTop);


        verticalLayout_2->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");

        verticalLayout_2->addLayout(gridLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        setEndButton = new QPushButton(centralwidget);
        setEndButton->setObjectName("setEndButton");

        gridLayout_2->addWidget(setEndButton, 2, 1, 1, 1);

        clearButton = new QPushButton(centralwidget);
        clearButton->setObjectName("clearButton");

        gridLayout_2->addWidget(clearButton, 3, 0, 1, 1);

        customButton = new QPushButton(centralwidget);
        customButton->setObjectName("customButton");

        gridLayout_2->addWidget(customButton, 2, 0, 1, 1);

        generateButton = new QPushButton(centralwidget);
        generateButton->setObjectName("generateButton");

        gridLayout_2->addWidget(generateButton, 0, 0, 1, 1);

        pauseButton = new QPushButton(centralwidget);
        pauseButton->setObjectName("pauseButton");

        gridLayout_2->addWidget(pauseButton, 2, 2, 1, 1);

        startButton = new QPushButton(centralwidget);
        startButton->setObjectName("startButton");

        gridLayout_2->addWidget(startButton, 0, 2, 1, 1);

        setStartButton = new QPushButton(centralwidget);
        setStartButton->setObjectName("setStartButton");

        gridLayout_2->addWidget(setStartButton, 0, 1, 1, 1);

        guantletButton = new QPushButton(centralwidget);
        guantletButton->setObjectName("guantletButton");

        gridLayout_2->addWidget(guantletButton, 6, 2, 1, 1);

        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName("resetButton");

        gridLayout_2->addWidget(resetButton, 3, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Maze Algorithms", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Algorithms:", nullptr));
        algorithmBox->setItemText(0, QCoreApplication::translate("MainWindow", "Dijkstra's", nullptr));
        algorithmBox->setItemText(1, QCoreApplication::translate("MainWindow", "Depth-First", nullptr));
        algorithmBox->setItemText(2, QCoreApplication::translate("MainWindow", "Breadth-First", nullptr));

        setEndButton->setText(QCoreApplication::translate("MainWindow", "Set End", nullptr));
        clearButton->setText(QCoreApplication::translate("MainWindow", "Clear Walls", nullptr));
        customButton->setText(QCoreApplication::translate("MainWindow", "Custom Maze", nullptr));
        generateButton->setText(QCoreApplication::translate("MainWindow", "Generate Maze", nullptr));
        pauseButton->setText(QCoreApplication::translate("MainWindow", "Pause Traversal", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "Start Traversal", nullptr));
        setStartButton->setText(QCoreApplication::translate("MainWindow", "Set Start", nullptr));
        guantletButton->setText(QCoreApplication::translate("MainWindow", "Algorithm Guantlet", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "Reset Algorithm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
