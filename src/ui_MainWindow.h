/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Wed Oct 5 18:36:05 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCalendarWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *m_openAction;
    QAction *m_addAction;
    QAction *m_submitAction;
    QAction *m_exitAction;
    QAction *m_saveAction;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *m_logoLabel;
    QCalendarWidget *m_calendarWidget;
    QLabel *m_amountLabel;
    QTableView *m_memberView;
    QSpacerItem *m_horizontalSpacer;
    QSpacerItem *m_horizontalSpacer_2;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(719, 486);
        MainWindow->setMinimumSize(QSize(0, 0));
        MainWindow->setMaximumSize(QSize(9998, 16777215));
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        MainWindow->setAutoFillBackground(true);
        MainWindow->setDocumentMode(false);
        m_openAction = new QAction(MainWindow);
        m_openAction->setObjectName(QString::fromUtf8("m_openAction"));
        m_addAction = new QAction(MainWindow);
        m_addAction->setObjectName(QString::fromUtf8("m_addAction"));
        m_submitAction = new QAction(MainWindow);
        m_submitAction->setObjectName(QString::fromUtf8("m_submitAction"));
        m_exitAction = new QAction(MainWindow);
        m_exitAction->setObjectName(QString::fromUtf8("m_exitAction"));
        m_saveAction = new QAction(MainWindow);
        m_saveAction->setObjectName(QString::fromUtf8("m_saveAction"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        m_logoLabel = new QLabel(centralwidget);
        m_logoLabel->setObjectName(QString::fromUtf8("m_logoLabel"));
        m_logoLabel->setMinimumSize(QSize(230, 190));
        m_logoLabel->setMaximumSize(QSize(230, 190));
        m_logoLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/szdiy_logo.png);"));

        gridLayout->addWidget(m_logoLabel, 0, 0, 1, 1);

        m_calendarWidget = new QCalendarWidget(centralwidget);
        m_calendarWidget->setObjectName(QString::fromUtf8("m_calendarWidget"));
        m_calendarWidget->setMinimumSize(QSize(255, 190));
        m_calendarWidget->setMaximumSize(QSize(280, 190));

        gridLayout->addWidget(m_calendarWidget, 0, 2, 1, 1);

        m_amountLabel = new QLabel(centralwidget);
        m_amountLabel->setObjectName(QString::fromUtf8("m_amountLabel"));
        m_amountLabel->setMinimumSize(QSize(190, 190));
        m_amountLabel->setMaximumSize(QSize(190, 190));

        gridLayout->addWidget(m_amountLabel, 0, 4, 1, 1);

        m_memberView = new QTableView(centralwidget);
        m_memberView->setObjectName(QString::fromUtf8("m_memberView"));

        gridLayout->addWidget(m_memberView, 1, 0, 1, 5);

        m_horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(m_horizontalSpacer, 0, 3, 1, 1);

        m_horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(m_horizontalSpacer_2, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 719, 26));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(m_addAction);
        menuFile->addAction(m_openAction);
        menuFile->addAction(m_saveAction);
        menuFile->addAction(m_submitAction);
        menuFile->addSeparator();
        menuFile->addAction(m_exitAction);

        retranslateUi(MainWindow);
        QObject::connect(m_exitAction, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        m_openAction->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        m_addAction->setText(QApplication::translate("MainWindow", "Add", 0, QApplication::UnicodeUTF8));
        m_submitAction->setText(QApplication::translate("MainWindow", "Submit", 0, QApplication::UnicodeUTF8));
        m_exitAction->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        m_saveAction->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
        m_logoLabel->setText(QString());
        m_amountLabel->setText(QApplication::translate("MainWindow", "Amount", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
