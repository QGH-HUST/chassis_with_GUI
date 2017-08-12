/********************************************************************************
** Form generated from reading UI file 'chassis_display.ui'
**
** Created: Tue Apr 4 10:44:21 2017
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHASSIS_DISPLAY_H
#define UI_CHASSIS_DISPLAY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chassis_display
{
public:
    QFrame *MOTOR;
    QLabel *label;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_3;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_6;
    QLineEdit *FLCPOS;
    QLineEdit *BLCPOS;
    QLabel *label_7;
    QLineEdit *FLTPOS;
    QLineEdit *BLTPOS;
    QLabel *label_8;
    QLineEdit *FLCVEL;
    QLineEdit *BLCVEL;
    QLabel *label_9;
    QLineEdit *FLTVEL;
    QLineEdit *BLTVEL;
    QLabel *label_10;
    QLineEdit *FLPVEL;
    QLineEdit *BLPVEL;
    QLabel *label_11;
    QLineEdit *FLEVEL;
    QLineEdit *BLEVEL;
    QLabel *label_13;
    QLineEdit *FLPACC;
    QLineEdit *BLPACC;
    QLabel *label_12;
    QLineEdit *FLPDEC;
    QLineEdit *BLPDEC;
    QFrame *CHASSIS;
    QLabel *label_2;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_2;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;
    QLabel *label_18;
    QLineEdit *CURRENTX;
    QLineEdit *CURRENTY;
    QLineEdit *CURRENTS;
    QLabel *label_19;
    QLineEdit *TRACKX;
    QLineEdit *TRACKY;
    QLineEdit *TRACKS;
    QLabel *label_20;
    QLineEdit *DESTX;
    QLineEdit *DESTY;
    QLineEdit *DESTS;
    QFrame *OTHER;
    QLabel *label_21;
    QLineEdit *CPPNUM;
    QLineEdit *AIMNUM;
    QLabel *label_22;
    QLabel *label_23;
    QFrame *OPERATE;
    QWidget *layoutWidget3;
    QGridLayout *gridLayout_4;
    QPushButton *OPENButton;
    QPushButton *CLOSEButton;
    QPushButton *STARTButton;
    QPushButton *STOPButton;
    QPushButton *PLANButton;
    QPushButton *TRACKButton;
    QFrame *ETHERCAT;
    QLabel *label_24;

    void setupUi(QDialog *chassis_display)
    {
        if (chassis_display->objectName().isEmpty())
            chassis_display->setObjectName(QString::fromUtf8("chassis_display"));
        chassis_display->resize(739, 572);
        chassis_display->setSizeGripEnabled(false);
        chassis_display->setModal(false);
        MOTOR = new QFrame(chassis_display);
        MOTOR->setObjectName(QString::fromUtf8("MOTOR"));
        MOTOR->setGeometry(QRect(10, 180, 461, 381));
        MOTOR->setFrameShape(QFrame::StyledPanel);
        MOTOR->setFrameShadow(QFrame::Raised);
        label = new QLabel(MOTOR);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 10, 96, 17));
        label->setLayoutDirection(Qt::LeftToRight);
        layoutWidget = new QWidget(MOTOR);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 33, 349, 283));
        gridLayout_3 = new QGridLayout(layoutWidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 0, 0, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 0, 1, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 0, 2, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 1, 0, 1, 1);

        FLCPOS = new QLineEdit(layoutWidget);
        FLCPOS->setObjectName(QString::fromUtf8("FLCPOS"));

        gridLayout_3->addWidget(FLCPOS, 1, 1, 1, 1);

        BLCPOS = new QLineEdit(layoutWidget);
        BLCPOS->setObjectName(QString::fromUtf8("BLCPOS"));

        gridLayout_3->addWidget(BLCPOS, 1, 2, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_3->addWidget(label_7, 2, 0, 1, 1);

        FLTPOS = new QLineEdit(layoutWidget);
        FLTPOS->setObjectName(QString::fromUtf8("FLTPOS"));

        gridLayout_3->addWidget(FLTPOS, 2, 1, 1, 1);

        BLTPOS = new QLineEdit(layoutWidget);
        BLTPOS->setObjectName(QString::fromUtf8("BLTPOS"));

        gridLayout_3->addWidget(BLTPOS, 2, 2, 1, 1);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_3->addWidget(label_8, 3, 0, 1, 1);

        FLCVEL = new QLineEdit(layoutWidget);
        FLCVEL->setObjectName(QString::fromUtf8("FLCVEL"));

        gridLayout_3->addWidget(FLCVEL, 3, 1, 1, 1);

        BLCVEL = new QLineEdit(layoutWidget);
        BLCVEL->setObjectName(QString::fromUtf8("BLCVEL"));

        gridLayout_3->addWidget(BLCVEL, 3, 2, 1, 1);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_3->addWidget(label_9, 4, 0, 1, 1);

        FLTVEL = new QLineEdit(layoutWidget);
        FLTVEL->setObjectName(QString::fromUtf8("FLTVEL"));

        gridLayout_3->addWidget(FLTVEL, 4, 1, 1, 1);

        BLTVEL = new QLineEdit(layoutWidget);
        BLTVEL->setObjectName(QString::fromUtf8("BLTVEL"));

        gridLayout_3->addWidget(BLTVEL, 4, 2, 1, 1);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_3->addWidget(label_10, 5, 0, 1, 1);

        FLPVEL = new QLineEdit(layoutWidget);
        FLPVEL->setObjectName(QString::fromUtf8("FLPVEL"));

        gridLayout_3->addWidget(FLPVEL, 5, 1, 1, 1);

        BLPVEL = new QLineEdit(layoutWidget);
        BLPVEL->setObjectName(QString::fromUtf8("BLPVEL"));

        gridLayout_3->addWidget(BLPVEL, 5, 2, 1, 1);

        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_3->addWidget(label_11, 6, 0, 1, 1);

        FLEVEL = new QLineEdit(layoutWidget);
        FLEVEL->setObjectName(QString::fromUtf8("FLEVEL"));

        gridLayout_3->addWidget(FLEVEL, 6, 1, 1, 1);

        BLEVEL = new QLineEdit(layoutWidget);
        BLEVEL->setObjectName(QString::fromUtf8("BLEVEL"));

        gridLayout_3->addWidget(BLEVEL, 6, 2, 1, 1);

        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_3->addWidget(label_13, 7, 0, 1, 1);

        FLPACC = new QLineEdit(layoutWidget);
        FLPACC->setObjectName(QString::fromUtf8("FLPACC"));

        gridLayout_3->addWidget(FLPACC, 7, 1, 1, 1);

        BLPACC = new QLineEdit(layoutWidget);
        BLPACC->setObjectName(QString::fromUtf8("BLPACC"));

        gridLayout_3->addWidget(BLPACC, 7, 2, 1, 1);

        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_3->addWidget(label_12, 8, 0, 1, 1);

        FLPDEC = new QLineEdit(layoutWidget);
        FLPDEC->setObjectName(QString::fromUtf8("FLPDEC"));

        gridLayout_3->addWidget(FLPDEC, 8, 1, 1, 1);

        BLPDEC = new QLineEdit(layoutWidget);
        BLPDEC->setObjectName(QString::fromUtf8("BLPDEC"));

        gridLayout_3->addWidget(BLPDEC, 8, 2, 1, 1);

        CHASSIS = new QFrame(chassis_display);
        CHASSIS->setObjectName(QString::fromUtf8("CHASSIS"));
        CHASSIS->setGeometry(QRect(10, 10, 461, 171));
        CHASSIS->setFrameShape(QFrame::StyledPanel);
        CHASSIS->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(CHASSIS);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(170, 0, 101, 17));
        layoutWidget1 = new QWidget(CHASSIS);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 30, 421, 19));
        gridLayout_2 = new QGridLayout(layoutWidget1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_14 = new QLabel(layoutWidget1);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_2->addWidget(label_14, 0, 0, 1, 1);

        label_15 = new QLabel(layoutWidget1);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_2->addWidget(label_15, 0, 1, 1, 1);

        label_16 = new QLabel(layoutWidget1);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_2->addWidget(label_16, 0, 2, 1, 1);

        label_17 = new QLabel(layoutWidget1);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_2->addWidget(label_17, 0, 3, 1, 1);

        layoutWidget2 = new QWidget(CHASSIS);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 50, 421, 95));
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_18 = new QLabel(layoutWidget2);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout->addWidget(label_18, 0, 0, 1, 1);

        CURRENTX = new QLineEdit(layoutWidget2);
        CURRENTX->setObjectName(QString::fromUtf8("CURRENTX"));
        CURRENTX->setReadOnly(false);

        gridLayout->addWidget(CURRENTX, 0, 1, 1, 1);

        CURRENTY = new QLineEdit(layoutWidget2);
        CURRENTY->setObjectName(QString::fromUtf8("CURRENTY"));

        gridLayout->addWidget(CURRENTY, 0, 2, 1, 1);

        CURRENTS = new QLineEdit(layoutWidget2);
        CURRENTS->setObjectName(QString::fromUtf8("CURRENTS"));

        gridLayout->addWidget(CURRENTS, 0, 3, 1, 1);

        label_19 = new QLabel(layoutWidget2);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout->addWidget(label_19, 1, 0, 1, 1);

        TRACKX = new QLineEdit(layoutWidget2);
        TRACKX->setObjectName(QString::fromUtf8("TRACKX"));

        gridLayout->addWidget(TRACKX, 1, 1, 1, 1);

        TRACKY = new QLineEdit(layoutWidget2);
        TRACKY->setObjectName(QString::fromUtf8("TRACKY"));

        gridLayout->addWidget(TRACKY, 1, 2, 1, 1);

        TRACKS = new QLineEdit(layoutWidget2);
        TRACKS->setObjectName(QString::fromUtf8("TRACKS"));

        gridLayout->addWidget(TRACKS, 1, 3, 1, 1);

        label_20 = new QLabel(layoutWidget2);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout->addWidget(label_20, 2, 0, 1, 1);

        DESTX = new QLineEdit(layoutWidget2);
        DESTX->setObjectName(QString::fromUtf8("DESTX"));

        gridLayout->addWidget(DESTX, 2, 1, 1, 1);

        DESTY = new QLineEdit(layoutWidget2);
        DESTY->setObjectName(QString::fromUtf8("DESTY"));

        gridLayout->addWidget(DESTY, 2, 2, 1, 1);

        DESTS = new QLineEdit(layoutWidget2);
        DESTS->setObjectName(QString::fromUtf8("DESTS"));

        gridLayout->addWidget(DESTS, 2, 3, 1, 1);

        OTHER = new QFrame(chassis_display);
        OTHER->setObjectName(QString::fromUtf8("OTHER"));
        OTHER->setGeometry(QRect(470, 10, 261, 171));
        OTHER->setFrameShape(QFrame::StyledPanel);
        OTHER->setFrameShadow(QFrame::Raised);
        label_21 = new QLabel(OTHER);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(60, 10, 141, 17));
        CPPNUM = new QLineEdit(OTHER);
        CPPNUM->setObjectName(QString::fromUtf8("CPPNUM"));
        CPPNUM->setGeometry(QRect(110, 30, 113, 27));
        AIMNUM = new QLineEdit(OTHER);
        AIMNUM->setObjectName(QString::fromUtf8("AIMNUM"));
        AIMNUM->setGeometry(QRect(110, 70, 113, 27));
        label_22 = new QLabel(OTHER);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(30, 30, 66, 17));
        label_23 = new QLabel(OTHER);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(30, 70, 66, 17));
        OPERATE = new QFrame(chassis_display);
        OPERATE->setObjectName(QString::fromUtf8("OPERATE"));
        OPERATE->setGeometry(QRect(470, 420, 261, 141));
        OPERATE->setFrameShape(QFrame::StyledPanel);
        OPERATE->setFrameShadow(QFrame::Raised);
        layoutWidget3 = new QWidget(OPERATE);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(20, 10, 231, 131));
        gridLayout_4 = new QGridLayout(layoutWidget3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        OPENButton = new QPushButton(layoutWidget3);
        OPENButton->setObjectName(QString::fromUtf8("OPENButton"));
        OPENButton->setDefault(false);

        gridLayout_4->addWidget(OPENButton, 0, 0, 1, 1);

        CLOSEButton = new QPushButton(layoutWidget3);
        CLOSEButton->setObjectName(QString::fromUtf8("CLOSEButton"));

        gridLayout_4->addWidget(CLOSEButton, 0, 1, 1, 1);

        STARTButton = new QPushButton(layoutWidget3);
        STARTButton->setObjectName(QString::fromUtf8("STARTButton"));
        STARTButton->setAutoDefault(true);

        gridLayout_4->addWidget(STARTButton, 1, 0, 1, 1);

        STOPButton = new QPushButton(layoutWidget3);
        STOPButton->setObjectName(QString::fromUtf8("STOPButton"));

        gridLayout_4->addWidget(STOPButton, 1, 1, 1, 1);

        PLANButton = new QPushButton(layoutWidget3);
        PLANButton->setObjectName(QString::fromUtf8("PLANButton"));

        gridLayout_4->addWidget(PLANButton, 2, 0, 1, 1);

        TRACKButton = new QPushButton(layoutWidget3);
        TRACKButton->setObjectName(QString::fromUtf8("TRACKButton"));

        gridLayout_4->addWidget(TRACKButton, 2, 1, 1, 1);

        ETHERCAT = new QFrame(chassis_display);
        ETHERCAT->setObjectName(QString::fromUtf8("ETHERCAT"));
        ETHERCAT->setGeometry(QRect(470, 180, 261, 241));
        ETHERCAT->setFrameShape(QFrame::StyledPanel);
        ETHERCAT->setFrameShadow(QFrame::Raised);
        label_24 = new QLabel(ETHERCAT);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(90, 10, 71, 17));
        QWidget::setTabOrder(OPENButton, CLOSEButton);
        QWidget::setTabOrder(CLOSEButton, STARTButton);
        QWidget::setTabOrder(STARTButton, STOPButton);
        QWidget::setTabOrder(STOPButton, PLANButton);
        QWidget::setTabOrder(PLANButton, TRACKButton);
        QWidget::setTabOrder(TRACKButton, AIMNUM);
        QWidget::setTabOrder(AIMNUM, CPPNUM);
        QWidget::setTabOrder(CPPNUM, CURRENTX);
        QWidget::setTabOrder(CURRENTX, CURRENTY);
        QWidget::setTabOrder(CURRENTY, CURRENTS);
        QWidget::setTabOrder(CURRENTS, TRACKX);
        QWidget::setTabOrder(TRACKX, TRACKY);
        QWidget::setTabOrder(TRACKY, TRACKS);
        QWidget::setTabOrder(TRACKS, DESTX);
        QWidget::setTabOrder(DESTX, DESTY);
        QWidget::setTabOrder(DESTY, DESTS);
        QWidget::setTabOrder(DESTS, FLCPOS);
        QWidget::setTabOrder(FLCPOS, BLCPOS);
        QWidget::setTabOrder(BLCPOS, FLTPOS);
        QWidget::setTabOrder(FLTPOS, BLTPOS);
        QWidget::setTabOrder(BLTPOS, FLCVEL);
        QWidget::setTabOrder(FLCVEL, BLCVEL);
        QWidget::setTabOrder(BLCVEL, FLTVEL);
        QWidget::setTabOrder(FLTVEL, BLTVEL);
        QWidget::setTabOrder(BLTVEL, FLPVEL);
        QWidget::setTabOrder(FLPVEL, BLPVEL);
        QWidget::setTabOrder(BLPVEL, FLEVEL);
        QWidget::setTabOrder(FLEVEL, BLEVEL);
        QWidget::setTabOrder(BLEVEL, FLPACC);
        QWidget::setTabOrder(FLPACC, BLPACC);
        QWidget::setTabOrder(BLPACC, FLPDEC);
        QWidget::setTabOrder(FLPDEC, BLPDEC);

        retranslateUi(chassis_display);

        QMetaObject::connectSlotsByName(chassis_display);
    } // setupUi

    void retranslateUi(QDialog *chassis_display)
    {
        chassis_display->setWindowTitle(QApplication::translate("chassis_display", "CHASSIS_PARA_DISPLAY", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("chassis_display", "Motor Display", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("chassis_display", "Parameter", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("chassis_display", "Motor FL", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("chassis_display", "Motor BL", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("chassis_display", "current pos", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("chassis_display", "target pos", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("chassis_display", "current vel", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("chassis_display", "target vel", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("chassis_display", "profile vel", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("chassis_display", "end vel", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("chassis_display", "profile acc", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("chassis_display", "profile dec", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("chassis_display", "Chassis Display", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("chassis_display", "Parameter", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("chassis_display", "ordinate x", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("chassis_display", "ordinate y", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("chassis_display", "ordinate sita", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("chassis_display", "CURRENT", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("chassis_display", "TRACKING", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("chassis_display", "DESTINATE", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("chassis_display", "OTHER PARAMETER", 0, QApplication::UnicodeUTF8));
        AIMNUM->setText(QApplication::translate("chassis_display", "0", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("chassis_display", "CPP NUM", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("chassis_display", "AIM NUM", 0, QApplication::UnicodeUTF8));
        OPENButton->setText(QApplication::translate("chassis_display", "OPEN", 0, QApplication::UnicodeUTF8));
        CLOSEButton->setText(QApplication::translate("chassis_display", "CLOSE", 0, QApplication::UnicodeUTF8));
        STARTButton->setText(QApplication::translate("chassis_display", "START", 0, QApplication::UnicodeUTF8));
        STOPButton->setText(QApplication::translate("chassis_display", "STOP", 0, QApplication::UnicodeUTF8));
        PLANButton->setText(QApplication::translate("chassis_display", "PLANNING", 0, QApplication::UnicodeUTF8));
        TRACKButton->setText(QApplication::translate("chassis_display", "TRACKING", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("chassis_display", "ETHERCAT", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class chassis_display: public Ui_chassis_display {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHASSIS_DISPLAY_H
