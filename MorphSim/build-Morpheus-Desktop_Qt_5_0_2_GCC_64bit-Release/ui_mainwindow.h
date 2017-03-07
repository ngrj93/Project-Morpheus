/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "horizontalsliderc.h"
#include "pushbuttonc.h"
#include "spinboxc.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QFrame *frame;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_7;
    QLabel *label_5;
    SpinBoxc *spinBox_8;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QSpinBox *spinBox;
    QLabel *label_3;
    SpinBoxc *spinBox_3;
    SpinBoxc *spinBox_6;
    QLabel *label;
    SpinBoxc *spinBox_5;
    QLabel *label_4;
    QLabel *label_6;
    SpinBoxc *spinBox_7;
    QLabel *label_10;
    SpinBoxc *spinBox_4;
    QLabel *label_9;
    QLabel *label_11;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    HorizontalSliderc *horizontalSlider_2;
    QTextEdit *textout;
    QFrame *frame_2;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *label_19;
    QPushButton *pushButton_7;
    QLabel *label_18;
    QLabel *label_2;
    QLabel *label_15;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QLabel *label_8;
    QSlider *horizontalSlider;
    QWidget *tab_2;
    QTextEdit *simres;
    QFrame *topbar;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    PushButtonc *pushButton;
    QSpacerItem *horizontalSpacer_2;
    PushButtonc *pushButton_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QButtonGroup *buttonGroup;
    QButtonGroup *buttonGroup_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1093, 576);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 40, 1211, 541));
        tabWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
        tabWidget->setStyleSheet(QLatin1String("#tabWidget{\n"
"margin-bottom:0;\n"
"}"));
        tabWidget->setTabShape(QTabWidget::Rounded);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        frame = new QFrame(tab);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 10, 401, 441));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayoutWidget = new QWidget(frame);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 381, 413));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setStyleSheet(QLatin1String("#label_7{\n"
"color:#000066;\n"
"}"));
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 6, 0, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setStyleSheet(QLatin1String("#label_5{\n"
"color:#000066;\n"
"}"));
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 7, 0, 1, 1);

        spinBox_8 = new SpinBoxc(gridLayoutWidget);
        spinBox_8->setObjectName(QStringLiteral("spinBox_8"));
        spinBox_8->setMinimum(2);
        spinBox_8->setMaximum(500);
        spinBox_8->setSingleStep(5);

        gridLayout->addWidget(spinBox_8, 4, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        radioButton = new QRadioButton(gridLayoutWidget);
        buttonGroup_2 = new QButtonGroup(MainWindow);
        buttonGroup_2->setObjectName(QStringLiteral("buttonGroup_2"));
        buttonGroup_2->addButton(radioButton);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setChecked(true);

        verticalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(gridLayoutWidget);
        buttonGroup_2->addButton(radioButton_2);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        verticalLayout->addWidget(radioButton_2);


        gridLayout->addLayout(verticalLayout, 3, 1, 1, 1);

        spinBox = new QSpinBox(gridLayoutWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimum(1);
        spinBox->setMaximum(1000);
        spinBox->setSingleStep(5);

        gridLayout->addWidget(spinBox, 0, 1, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        spinBox_3 = new SpinBoxc(gridLayoutWidget);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setEnabled(false);
        spinBox_3->setMinimum(0);
        spinBox_3->setSingleStep(3);

        gridLayout->addWidget(spinBox_3, 8, 1, 1, 1);

        spinBox_6 = new SpinBoxc(gridLayoutWidget);
        spinBox_6->setObjectName(QStringLiteral("spinBox_6"));
        spinBox_6->setEnabled(false);
        spinBox_6->setMinimum(1);
        spinBox_6->setSingleStep(3);

        gridLayout->addWidget(spinBox_6, 5, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spinBox_5 = new SpinBoxc(gridLayoutWidget);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));
        spinBox_5->setEnabled(false);
        spinBox_5->setMinimum(1);
        spinBox_5->setSingleStep(3);

        gridLayout->addWidget(spinBox_5, 6, 1, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setStyleSheet(QLatin1String("#label_4{\n"
"color:#000066;\n"
"}"));
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 5, 0, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setStyleSheet(QLatin1String("#label_6{\n"
"color:#000066;\n"
"}"));
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_6, 8, 0, 1, 1);

        spinBox_7 = new SpinBoxc(gridLayoutWidget);
        spinBox_7->setObjectName(QStringLiteral("spinBox_7"));
        spinBox_7->setMinimum(2);
        spinBox_7->setMaximum(50);
        spinBox_7->setSingleStep(3);

        gridLayout->addWidget(spinBox_7, 1, 1, 1, 1);

        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_10, 4, 0, 1, 1);

        spinBox_4 = new SpinBoxc(gridLayoutWidget);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));
        spinBox_4->setEnabled(false);
        spinBox_4->setMinimum(0);
        spinBox_4->setSingleStep(3);

        gridLayout->addWidget(spinBox_4, 7, 1, 1, 1);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_9, 1, 0, 1, 1);

        label_11 = new QLabel(gridLayoutWidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 2, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        radioButton_3 = new QRadioButton(gridLayoutWidget);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(radioButton_3);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setChecked(true);

        verticalLayout_2->addWidget(radioButton_3);

        radioButton_4 = new QRadioButton(gridLayoutWidget);
        buttonGroup->addButton(radioButton_4);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));

        verticalLayout_2->addWidget(radioButton_4);

        horizontalSlider_2 = new HorizontalSliderc(gridLayoutWidget);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setEnabled(false);
        horizontalSlider_2->setMinimum(1);
        horizontalSlider_2->setMaximum(10);
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(horizontalSlider_2);


        gridLayout->addLayout(verticalLayout_2, 2, 1, 1, 1);

        textout = new QTextEdit(tab);
        textout->setObjectName(QStringLiteral("textout"));
        textout->setGeometry(QRect(420, 10, 341, 441));
        textout->setReadOnly(true);
        frame_2 = new QFrame(tab);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(770, 10, 311, 291));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayoutWidget_2 = new QWidget(frame_2);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 10, 291, 271));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_19 = new QLabel(gridLayoutWidget_2);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_19, 1, 0, 1, 1);

        pushButton_7 = new QPushButton(gridLayoutWidget_2);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        gridLayout_2->addWidget(pushButton_7, 3, 1, 1, 1);

        label_18 = new QLabel(gridLayoutWidget_2);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_18, 3, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        label_15 = new QLabel(gridLayoutWidget_2);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_2->addWidget(label_15, 2, 0, 1, 1);

        pushButton_4 = new QPushButton(gridLayoutWidget_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout_2->addWidget(pushButton_4, 0, 1, 1, 1);

        pushButton_5 = new QPushButton(gridLayoutWidget_2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout_2->addWidget(pushButton_5, 1, 1, 1, 1);

        pushButton_6 = new QPushButton(gridLayoutWidget_2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        gridLayout_2->addWidget(pushButton_6, 2, 1, 1, 1);

        label_8 = new QLabel(gridLayoutWidget_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 4, 0, 1, 1);

        horizontalSlider = new QSlider(gridLayoutWidget_2);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMinimum(0);
        horizontalSlider->setMaximum(5);
        horizontalSlider->setSingleStep(1);
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalSlider, 4, 1, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        simres = new QTextEdit(tab_2);
        simres->setObjectName(QStringLiteral("simres"));
        simres->setGeometry(QRect(10, 10, 1071, 441));
        simres->setReadOnly(true);
        tabWidget->addTab(tab_2, QString());
        topbar = new QFrame(centralWidget);
        topbar->setObjectName(QStringLiteral("topbar"));
        topbar->setGeometry(QRect(0, 0, 1211, 41));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(topbar->sizePolicy().hasHeightForWidth());
        topbar->setSizePolicy(sizePolicy1);
        topbar->setStyleSheet(QLatin1String("#topbar {\n"
"border: none;\n"
"background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"stop: 0 #56544C, stop: 0.08 #56544C,\n"
"stop: 0.39999 #56544C, stop: 0.4 #56544C,\n"
"stop: 0.9 #3F3E3A, stop: 1 #3F3E3A);\n"
"}\n"
""));
        topbar->setFrameShape(QFrame::StyledPanel);
        topbar->setFrameShadow(QFrame::Raised);
        horizontalLayoutWidget = new QWidget(topbar);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 403, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        pushButton = new PushButtonc(horizontalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setStyleSheet(QLatin1String("#pushButton:hover{\n"
"color:rgb(0, 170, 127);\n"
"}"));
        pushButton->setFlat(false);

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_2 = new PushButtonc(horizontalLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setEnabled(false);
        pushButton_2->setStyleSheet(QLatin1String("#pushButton_2:hover{\n"
"color:rgb(170, 0, 0);\n"
"}"));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton_3 = new QPushButton(horizontalLayoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        horizontalSpacer = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1093, 25));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MorphSim v2.0", 0));
        label_7->setText(QApplication::translate("MainWindow", "Number of Positive Nodes:", 0));
        label_5->setText(QApplication::translate("MainWindow", "Number of Negative Nodes:", 0));
        radioButton->setText(QApplication::translate("MainWindow", "Random", 0));
        radioButton_2->setText(QApplication::translate("MainWindow", "Manual", 0));
        label_3->setText(QApplication::translate("MainWindow", "Node State Assignment:", 0));
        label->setText(QApplication::translate("MainWindow", "Number of Jobs to be Processed:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Number of Suprapositive Nodes:", 0));
        label_6->setText(QApplication::translate("MainWindow", "Number of Neutral Nodes:", 0));
        label_10->setText(QApplication::translate("MainWindow", "Number of Compute Nodes:", 0));
        label_9->setText(QApplication::translate("MainWindow", "Approximate Neighbour Count:", 0));
        label_11->setText(QApplication::translate("MainWindow", "Job Burst Size:", 0));
        radioButton_3->setText(QApplication::translate("MainWindow", "Random", 0));
        radioButton_4->setText(QApplication::translate("MainWindow", "Ranged", 0));
        label_19->setText(QApplication::translate("MainWindow", "Remove random node:", 0));
        pushButton_7->setText(QApplication::translate("MainWindow", "Job--", 0));
        label_18->setText(QApplication::translate("MainWindow", "Remove random job:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Introduce new node:", 0));
        label_15->setText(QApplication::translate("MainWindow", "Introduce new job:", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "Node++", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "Node--", 0));
        pushButton_6->setText(QApplication::translate("MainWindow", "Job++", 0));
        label_8->setText(QApplication::translate("MainWindow", "Unforseen Loss Probability:", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Simulation", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Statistics", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Start Simulation", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Stop Simulation", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Generate Log", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
