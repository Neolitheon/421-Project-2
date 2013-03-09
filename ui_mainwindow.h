/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Mar 9 11:12:32 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <display.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    Display *display;
    QFrame *frame;
    QGridLayout *gridLayout;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QLabel *label;
    QFrame *frame_3;
    QGridLayout *gridLayout_3;
    QLabel *label_2;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_7;
    QFrame *frame_4;
    QGridLayout *gridLayout_4;
    QRadioButton *radioButton_8;
    QRadioButton *radioButton_9;
    QFrame *frame_5;
    QGridLayout *gridLayout_5;
    QSlider *horizontalSlider;
    QSlider *horizontalSlider_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QSlider *horizontalSlider_3;
    QLCDNumber *lcdNumber_2;
    QLCDNumber *lcdNumber_3;
    QLCDNumber *lcdNumber;
    QFrame *frame_6;
    QVBoxLayout *verticalLayout;
    QPushButton *start;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(743, 750);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        display = new Display(centralWidget);
        display->setObjectName(QString::fromUtf8("display"));

        horizontalLayout->addWidget(display);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMaximumSize(QSize(200, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        radioButton = new QRadioButton(frame_2);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setChecked(true);

        gridLayout_2->addWidget(radioButton, 1, 0, 1, 1);

        radioButton_2 = new QRadioButton(frame_2);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        gridLayout_2->addWidget(radioButton_2, 2, 0, 1, 1);

        radioButton_3 = new QRadioButton(frame_2);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        gridLayout_2->addWidget(radioButton_3, 3, 0, 1, 1);

        radioButton_4 = new QRadioButton(frame_2);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));

        gridLayout_2->addWidget(radioButton_4, 4, 0, 1, 1);

        label = new QLabel(frame_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);


        gridLayout->addWidget(frame_2, 1, 0, 1, 2);

        frame_3 = new QFrame(frame);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_2 = new QLabel(frame_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 0, 0, 1, 1);

        radioButton_5 = new QRadioButton(frame_3);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));
        radioButton_5->setChecked(true);

        gridLayout_3->addWidget(radioButton_5, 1, 0, 1, 1);

        radioButton_6 = new QRadioButton(frame_3);
        radioButton_6->setObjectName(QString::fromUtf8("radioButton_6"));

        gridLayout_3->addWidget(radioButton_6, 2, 0, 1, 1);

        radioButton_7 = new QRadioButton(frame_3);
        radioButton_7->setObjectName(QString::fromUtf8("radioButton_7"));

        gridLayout_3->addWidget(radioButton_7, 3, 0, 1, 1);


        gridLayout->addWidget(frame_3, 3, 0, 1, 2);

        frame_4 = new QFrame(frame);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        radioButton_8 = new QRadioButton(frame_4);
        radioButton_8->setObjectName(QString::fromUtf8("radioButton_8"));
        radioButton_8->setChecked(false);

        gridLayout_4->addWidget(radioButton_8, 0, 0, 1, 1);

        radioButton_9 = new QRadioButton(frame_4);
        radioButton_9->setObjectName(QString::fromUtf8("radioButton_9"));
        radioButton_9->setChecked(true);

        gridLayout_4->addWidget(radioButton_9, 1, 0, 1, 1);


        gridLayout->addWidget(frame_4, 4, 0, 1, 2);

        frame_5 = new QFrame(frame);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame_5);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalSlider = new QSlider(frame_5);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(20);
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(horizontalSlider, 1, 0, 1, 1);

        horizontalSlider_2 = new QSlider(frame_5);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setMinimum(1);
        horizontalSlider_2->setMaximum(4);
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(horizontalSlider_2, 5, 0, 1, 1);

        label_3 = new QLabel(frame_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_5->addWidget(label_3, 0, 0, 1, 2);

        label_4 = new QLabel(frame_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_5->addWidget(label_4, 4, 0, 1, 2);

        label_5 = new QLabel(frame_5);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_5->addWidget(label_5, 2, 0, 1, 2);

        horizontalSlider_3 = new QSlider(frame_5);
        horizontalSlider_3->setObjectName(QString::fromUtf8("horizontalSlider_3"));
        horizontalSlider_3->setMinimum(10);
        horizontalSlider_3->setMaximum(33);
        horizontalSlider_3->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(horizontalSlider_3, 3, 0, 1, 1);

        lcdNumber_2 = new QLCDNumber(frame_5);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));
        lcdNumber_2->setProperty("value", QVariant(10));

        gridLayout_5->addWidget(lcdNumber_2, 3, 1, 1, 1);

        lcdNumber_3 = new QLCDNumber(frame_5);
        lcdNumber_3->setObjectName(QString::fromUtf8("lcdNumber_3"));
        lcdNumber_3->setProperty("value", QVariant(1));

        gridLayout_5->addWidget(lcdNumber_3, 5, 1, 1, 1);

        lcdNumber = new QLCDNumber(frame_5);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setProperty("value", QVariant(1));

        gridLayout_5->addWidget(lcdNumber, 1, 1, 1, 1);


        gridLayout->addWidget(frame_5, 5, 0, 1, 2);

        frame_6 = new QFrame(frame);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_6);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        start = new QPushButton(frame_6);
        start->setObjectName(QString::fromUtf8("start"));

        verticalLayout->addWidget(start);

        label_6 = new QLabel(frame_6);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout->addWidget(label_6);

        label_7 = new QLabel(frame_6);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout->addWidget(label_7);

        label_8 = new QLabel(frame_6);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout->addWidget(label_8);

        label_9 = new QLabel(frame_6);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout->addWidget(label_9);


        gridLayout->addWidget(frame_6, 0, 0, 1, 2);


        horizontalLayout->addWidget(frame);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 743, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("MainWindow", "Iris-setosa", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("MainWindow", "Iris-versicolor", 0, QApplication::UnicodeUTF8));
        radioButton_3->setText(QApplication::translate("MainWindow", "Iris-virginica", 0, QApplication::UnicodeUTF8));
        radioButton_4->setText(QApplication::translate("MainWindow", "Blood.", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Data Set", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Algorithim", 0, QApplication::UnicodeUTF8));
        radioButton_5->setText(QApplication::translate("MainWindow", "Kernel - Polynomial", 0, QApplication::UnicodeUTF8));
        radioButton_6->setText(QApplication::translate("MainWindow", "Kernel - Gaussian", 0, QApplication::UnicodeUTF8));
        radioButton_7->setText(QApplication::translate("MainWindow", "Boosting", 0, QApplication::UnicodeUTF8));
        radioButton_8->setText(QApplication::translate("MainWindow", "Analyse", 0, QApplication::UnicodeUTF8));
        radioButton_9->setText(QApplication::translate("MainWindow", "Run one data set", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Max Iterations", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Perceptron Dimensions", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Training Set (%)", 0, QApplication::UnicodeUTF8));
        start->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "X axis: # of iterations", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Y axis: training set size", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Origin: top left", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Green = high accuracy", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
