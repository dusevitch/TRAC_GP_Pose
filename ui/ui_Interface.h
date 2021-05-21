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
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
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
    QGroupBox *groupHapticLin;
    QGridLayout *gridLayoutHaptic;
    QLabel *titleZoom;
    QSlider *sliderZoom;
    QLabel *labelZoom;
    QPushButton *setBasePosition;
    QFrame *frame;
    QLCDNumber *pos_x;
    QLCDNumber *pos_y;
    QLCDNumber *lcdNumber_3;
    QSpacerItem *verticalSpacer;
    QPushButton *alignCamera;
    QPushButton *updateStaticMarkers;
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
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Settings->sizePolicy().hasHeightForWidth());
        Settings->setSizePolicy(sizePolicy);
        Settings->setMinimumSize(QSize(300, 0));
        Settings->setMaximumSize(QSize(300, 16777215));
        Settings->setAutoFillBackground(true);
        verticalLayout = new QVBoxLayout(Settings);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupHapticLin = new QGroupBox(Settings);
        groupHapticLin->setObjectName(QString::fromUtf8("groupHapticLin"));
        groupHapticLin->setEnabled(true);
        gridLayoutHaptic = new QGridLayout(groupHapticLin);
        gridLayoutHaptic->setSpacing(6);
        gridLayoutHaptic->setContentsMargins(11, 11, 11, 11);
        gridLayoutHaptic->setObjectName(QString::fromUtf8("gridLayoutHaptic"));
        titleZoom = new QLabel(groupHapticLin);
        titleZoom->setObjectName(QString::fromUtf8("titleZoom"));
        titleZoom->setEnabled(true);

        gridLayoutHaptic->addWidget(titleZoom, 0, 0, 1, 1);

        sliderZoom = new QSlider(groupHapticLin);
        sliderZoom->setObjectName(QString::fromUtf8("sliderZoom"));
        sliderZoom->setEnabled(true);
        sliderZoom->setMaximum(100);
        sliderZoom->setOrientation(Qt::Horizontal);

        gridLayoutHaptic->addWidget(sliderZoom, 0, 2, 1, 1);

        labelZoom = new QLabel(groupHapticLin);
        labelZoom->setObjectName(QString::fromUtf8("labelZoom"));
        labelZoom->setEnabled(true);
        labelZoom->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutHaptic->addWidget(labelZoom, 0, 3, 1, 1);


        verticalLayout->addWidget(groupHapticLin);

        setBasePosition = new QPushButton(Settings);
        setBasePosition->setObjectName(QString::fromUtf8("setBasePosition"));
        setBasePosition->setEnabled(true);

        verticalLayout->addWidget(setBasePosition);

        frame = new QFrame(Settings);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pos_x = new QLCDNumber(frame);
        pos_x->setObjectName(QString::fromUtf8("pos_x"));
        pos_x->setGeometry(QRect(20, 10, 64, 23));
        pos_y = new QLCDNumber(frame);
        pos_y->setObjectName(QString::fromUtf8("pos_y"));
        pos_y->setGeometry(QRect(110, 10, 64, 23));
        lcdNumber_3 = new QLCDNumber(frame);
        lcdNumber_3->setObjectName(QString::fromUtf8("lcdNumber_3"));
        lcdNumber_3->setGeometry(QRect(200, 10, 64, 23));

        verticalLayout->addWidget(frame);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        alignCamera = new QPushButton(Settings);
        alignCamera->setObjectName(QString::fromUtf8("alignCamera"));

        verticalLayout->addWidget(alignCamera);

        updateStaticMarkers = new QPushButton(Settings);
        updateStaticMarkers->setObjectName(QString::fromUtf8("updateStaticMarkers"));

        verticalLayout->addWidget(updateStaticMarkers);


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
        groupHapticLin->setTitle(QApplication::translate("InterfaceClass", "Application Parameters", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        titleZoom->setToolTip(QApplication::translate("InterfaceClass", "Scaling factor between haptic translation and robot translation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        titleZoom->setText(QApplication::translate("InterfaceClass", "Zoom", 0, QApplication::UnicodeUTF8));
        labelZoom->setText(QApplication::translate("InterfaceClass", "000.0", 0, QApplication::UnicodeUTF8));
        setBasePosition->setText(QApplication::translate("InterfaceClass", "Set Base Position", 0, QApplication::UnicodeUTF8));
        alignCamera->setText(QApplication::translate("InterfaceClass", "Align Camera to Base Marker", 0, QApplication::UnicodeUTF8));
        updateStaticMarkers->setText(QApplication::translate("InterfaceClass", "Update Static Marker Data", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("InterfaceClass", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class InterfaceClass: public Ui_InterfaceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE_H
