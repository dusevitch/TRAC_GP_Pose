/********************************************************************************
** Form generated from reading UI file 'Interface.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InterfaceClass
{
public:
    QAction *actionShow_Settings;
    QAction *actionFull_Screen;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *Settings;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QGroupBox *groupBox_2;
    QLabel *label_28;
    QLCDNumber *objframe_x;
    QLCDNumber *objframe_y;
    QLCDNumber *base_x;
    QLCDNumber *base_y;
    QLabel *label_2;
    QLCDNumber *tool_x;
    QLabel *label;
    QLCDNumber *tool_y;
    QLCDNumber *base_z;
    QLCDNumber *objframe_z;
    QLCDNumber *tool_z;
    QPushButton *pushButton;
    QLabel *gp_file_label;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *hide_show_base;
    QPushButton *hide_show_tool;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *x_neg;
    QLabel *X_arrow_disp;
    QPushButton *x_pos;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *y_neg;
    QLabel *Y_arrow_disp;
    QPushButton *y_pos;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *z_neg;
    QLabel *Z_arrow_disp;
    QPushButton *z_pos;
    QPushButton *alignCamera;
    QPushButton *updateStaticMarkers;
    QPushButton *setBasePosition;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *zoom_out;
    QLabel *Zoom_Label;
    QPushButton *zoom_in;
    QToolBar *toolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *InterfaceClass)
    {
        if (InterfaceClass->objectName().isEmpty())
            InterfaceClass->setObjectName(QString::fromUtf8("InterfaceClass"));
        InterfaceClass->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/chai3d.ico"), QSize(), QIcon::Normal, QIcon::Off);
        InterfaceClass->setWindowIcon(icon);
        actionShow_Settings = new QAction(InterfaceClass);
        actionShow_Settings->setObjectName(QString::fromUtf8("actionShow_Settings"));
        actionShow_Settings->setCheckable(true);
        actionFull_Screen = new QAction(InterfaceClass);
        actionFull_Screen->setObjectName(QString::fromUtf8("actionFull_Screen"));
        actionFull_Screen->setCheckable(true);
        centralWidget = new QWidget(InterfaceClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Settings = new QWidget(centralWidget);
        Settings->setObjectName(QString::fromUtf8("Settings"));
        Settings->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Settings->sizePolicy().hasHeightForWidth());
        Settings->setSizePolicy(sizePolicy);
        Settings->setMinimumSize(QSize(300, 0));
        Settings->setMaximumSize(QSize(300, 16777215));
        QFont font;
        font.setKerning(true);
        Settings->setFont(font);
        Settings->setAutoFillBackground(true);
        verticalLayout = new QVBoxLayout(Settings);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(Settings);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 271, 141));
        label_28 = new QLabel(groupBox_2);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(10, 110, 41, 20));
        objframe_x = new QLCDNumber(groupBox_2);
        objframe_x->setObjectName(QString::fromUtf8("objframe_x"));
        objframe_x->setGeometry(QRect(50, 20, 64, 23));
        objframe_y = new QLCDNumber(groupBox_2);
        objframe_y->setObjectName(QString::fromUtf8("objframe_y"));
        objframe_y->setGeometry(QRect(120, 20, 64, 23));
        base_x = new QLCDNumber(groupBox_2);
        base_x->setObjectName(QString::fromUtf8("base_x"));
        base_x->setGeometry(QRect(50, 110, 64, 23));
        base_y = new QLCDNumber(groupBox_2);
        base_y->setObjectName(QString::fromUtf8("base_y"));
        base_y->setGeometry(QRect(120, 110, 64, 23));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 50, 31, 16));
        tool_x = new QLCDNumber(groupBox_2);
        tool_x->setObjectName(QString::fromUtf8("tool_x"));
        tool_x->setGeometry(QRect(50, 50, 64, 23));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 51, 20));
        tool_y = new QLCDNumber(groupBox_2);
        tool_y->setObjectName(QString::fromUtf8("tool_y"));
        tool_y->setGeometry(QRect(120, 50, 64, 23));
        base_z = new QLCDNumber(groupBox_2);
        base_z->setObjectName(QString::fromUtf8("base_z"));
        base_z->setGeometry(QRect(190, 110, 64, 23));
        objframe_z = new QLCDNumber(groupBox_2);
        objframe_z->setObjectName(QString::fromUtf8("objframe_z"));
        objframe_z->setGeometry(QRect(190, 20, 64, 23));
        tool_z = new QLCDNumber(groupBox_2);
        tool_z->setObjectName(QString::fromUtf8("tool_z"));
        tool_z->setGeometry(QRect(190, 50, 64, 23));
        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 170, 121, 22));
        gp_file_label = new QLabel(frame);
        gp_file_label->setObjectName(QString::fromUtf8("gp_file_label"));
        gp_file_label->setGeometry(QRect(148, 170, 101, 20));

        verticalLayout->addWidget(frame);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        hide_show_base = new QPushButton(Settings);
        hide_show_base->setObjectName(QString::fromUtf8("hide_show_base"));
        hide_show_base->setCheckable(true);

        horizontalLayout_2->addWidget(hide_show_base);

        hide_show_tool = new QPushButton(Settings);
        hide_show_tool->setObjectName(QString::fromUtf8("hide_show_tool"));
        hide_show_tool->setCheckable(true);

        horizontalLayout_2->addWidget(hide_show_tool);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        x_neg = new QPushButton(Settings);
        x_neg->setObjectName(QString::fromUtf8("x_neg"));
        x_neg->setStyleSheet(QString::fromUtf8("background-color: gray;"));
        x_neg->setCheckable(true);

        horizontalLayout_5->addWidget(x_neg);

        X_arrow_disp = new QLabel(Settings);
        X_arrow_disp->setObjectName(QString::fromUtf8("X_arrow_disp"));
        X_arrow_disp->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(X_arrow_disp);

        x_pos = new QPushButton(Settings);
        x_pos->setObjectName(QString::fromUtf8("x_pos"));
        x_pos->setStyleSheet(QString::fromUtf8("background-color: gray;"));
        x_pos->setCheckable(true);

        horizontalLayout_5->addWidget(x_pos);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        y_neg = new QPushButton(Settings);
        y_neg->setObjectName(QString::fromUtf8("y_neg"));
        y_neg->setStyleSheet(QString::fromUtf8("background-color: gray;"));
        y_neg->setCheckable(true);

        horizontalLayout_6->addWidget(y_neg);

        Y_arrow_disp = new QLabel(Settings);
        Y_arrow_disp->setObjectName(QString::fromUtf8("Y_arrow_disp"));
        Y_arrow_disp->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(Y_arrow_disp);

        y_pos = new QPushButton(Settings);
        y_pos->setObjectName(QString::fromUtf8("y_pos"));
        y_pos->setStyleSheet(QString::fromUtf8("background-color: gray;"));
        y_pos->setCheckable(true);

        horizontalLayout_6->addWidget(y_pos);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        z_neg = new QPushButton(Settings);
        z_neg->setObjectName(QString::fromUtf8("z_neg"));
        z_neg->setStyleSheet(QString::fromUtf8("background-color: gray;"));
        z_neg->setCheckable(true);

        horizontalLayout_7->addWidget(z_neg);

        Z_arrow_disp = new QLabel(Settings);
        Z_arrow_disp->setObjectName(QString::fromUtf8("Z_arrow_disp"));
        Z_arrow_disp->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(Z_arrow_disp);

        z_pos = new QPushButton(Settings);
        z_pos->setObjectName(QString::fromUtf8("z_pos"));
        z_pos->setStyleSheet(QString::fromUtf8("background-color: gray;"));
        z_pos->setCheckable(true);

        horizontalLayout_7->addWidget(z_pos);


        verticalLayout->addLayout(horizontalLayout_7);

        alignCamera = new QPushButton(Settings);
        alignCamera->setObjectName(QString::fromUtf8("alignCamera"));

        verticalLayout->addWidget(alignCamera);

        updateStaticMarkers = new QPushButton(Settings);
        updateStaticMarkers->setObjectName(QString::fromUtf8("updateStaticMarkers"));

        verticalLayout->addWidget(updateStaticMarkers);

        setBasePosition = new QPushButton(Settings);
        setBasePosition->setObjectName(QString::fromUtf8("setBasePosition"));
        setBasePosition->setEnabled(true);

        verticalLayout->addWidget(setBasePosition);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        zoom_out = new QPushButton(Settings);
        zoom_out->setObjectName(QString::fromUtf8("zoom_out"));

        horizontalLayout_3->addWidget(zoom_out);

        Zoom_Label = new QLabel(Settings);
        Zoom_Label->setObjectName(QString::fromUtf8("Zoom_Label"));
        Zoom_Label->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(Zoom_Label);

        zoom_in = new QPushButton(Settings);
        zoom_in->setObjectName(QString::fromUtf8("zoom_in"));

        horizontalLayout_3->addWidget(zoom_in);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout->addWidget(Settings);

        InterfaceClass->setCentralWidget(centralWidget);
        toolBar = new QToolBar(InterfaceClass);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setAutoFillBackground(true);
        toolBar->setMovable(false);
        toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolBar->setFloatable(false);
        InterfaceClass->addToolBar(Qt::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(InterfaceClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        InterfaceClass->setStatusBar(statusBar);

        toolBar->addAction(actionShow_Settings);
        toolBar->addAction(actionFull_Screen);

        retranslateUi(InterfaceClass);
        QObject::connect(actionShow_Settings, SIGNAL(triggered(bool)), Settings, SLOT(setVisible(bool)));

        QMetaObject::connectSlotsByName(InterfaceClass);
    } // setupUi

    void retranslateUi(QMainWindow *InterfaceClass)
    {
        InterfaceClass->setWindowTitle(QApplication::translate("InterfaceClass", "CHAI3D", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        InterfaceClass->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        actionShow_Settings->setText(QApplication::translate("InterfaceClass", "Settings", 0, QApplication::UnicodeUTF8));
        actionFull_Screen->setText(QApplication::translate("InterfaceClass", "Fullscreen", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("InterfaceClass", "POSITIONS", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("InterfaceClass", "BASE", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("InterfaceClass", "OBJ 2", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("InterfaceClass", "OBJ 1", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("InterfaceClass", "Load GP File", 0, QApplication::UnicodeUTF8));
        gp_file_label->setText(QApplication::translate("InterfaceClass", "No file selected", 0, QApplication::UnicodeUTF8));
        hide_show_base->setText(QApplication::translate("InterfaceClass", "Hide Base", 0, QApplication::UnicodeUTF8));
        hide_show_tool->setText(QApplication::translate("InterfaceClass", "Hide Tool", 0, QApplication::UnicodeUTF8));
        x_neg->setText(QApplication::translate("InterfaceClass", "neg", 0, QApplication::UnicodeUTF8));
        X_arrow_disp->setText(QApplication::translate("InterfaceClass", "Disp X Arrow", 0, QApplication::UnicodeUTF8));
        x_pos->setText(QApplication::translate("InterfaceClass", "pos", 0, QApplication::UnicodeUTF8));
        y_neg->setText(QApplication::translate("InterfaceClass", "neg", 0, QApplication::UnicodeUTF8));
        Y_arrow_disp->setText(QApplication::translate("InterfaceClass", "Disp Y Arrow", 0, QApplication::UnicodeUTF8));
        y_pos->setText(QApplication::translate("InterfaceClass", "pos", 0, QApplication::UnicodeUTF8));
        z_neg->setText(QApplication::translate("InterfaceClass", "neg", 0, QApplication::UnicodeUTF8));
        Z_arrow_disp->setText(QApplication::translate("InterfaceClass", "Disp Z Arrow", 0, QApplication::UnicodeUTF8));
        z_pos->setText(QApplication::translate("InterfaceClass", "pos", 0, QApplication::UnicodeUTF8));
        alignCamera->setText(QApplication::translate("InterfaceClass", "Align Camera to Base Marker", 0, QApplication::UnicodeUTF8));
        updateStaticMarkers->setText(QApplication::translate("InterfaceClass", "Update Static Marker Data", 0, QApplication::UnicodeUTF8));
        setBasePosition->setText(QApplication::translate("InterfaceClass", "Set Base Position", 0, QApplication::UnicodeUTF8));
        zoom_out->setText(QApplication::translate("InterfaceClass", "-", 0, QApplication::UnicodeUTF8));
        Zoom_Label->setText(QApplication::translate("InterfaceClass", "Zoom", 0, QApplication::UnicodeUTF8));
        zoom_in->setText(QApplication::translate("InterfaceClass", "+", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("InterfaceClass", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class InterfaceClass: public Ui_InterfaceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE_H
