/********************************************************************************
** Form generated from reading UI file 'DataAnalyze.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAANALYZE_H
#define UI_DATAANALYZE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataAnalyzeClass
{
public:
    QAction *actionopen;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menutest;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DataAnalyzeClass)
    {
        if (DataAnalyzeClass->objectName().isEmpty())
            DataAnalyzeClass->setObjectName(QStringLiteral("DataAnalyzeClass"));
        DataAnalyzeClass->resize(704, 462);
        actionopen = new QAction(DataAnalyzeClass);
        actionopen->setObjectName(QStringLiteral("actionopen"));
        centralWidget = new QWidget(DataAnalyzeClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        DataAnalyzeClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DataAnalyzeClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 704, 26));
        menutest = new QMenu(menuBar);
        menutest->setObjectName(QStringLiteral("menutest"));
        DataAnalyzeClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DataAnalyzeClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DataAnalyzeClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DataAnalyzeClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DataAnalyzeClass->setStatusBar(statusBar);

        menuBar->addAction(menutest->menuAction());
        menutest->addAction(actionopen);

        retranslateUi(DataAnalyzeClass);

        QMetaObject::connectSlotsByName(DataAnalyzeClass);
    } // setupUi

    void retranslateUi(QMainWindow *DataAnalyzeClass)
    {
        DataAnalyzeClass->setWindowTitle(QApplication::translate("DataAnalyzeClass", "DataAnalyze", Q_NULLPTR));
        actionopen->setText(QApplication::translate("DataAnalyzeClass", "open", Q_NULLPTR));
        menutest->setTitle(QApplication::translate("DataAnalyzeClass", "test", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DataAnalyzeClass: public Ui_DataAnalyzeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAANALYZE_H
