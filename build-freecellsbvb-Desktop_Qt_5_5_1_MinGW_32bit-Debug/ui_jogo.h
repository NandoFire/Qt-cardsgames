/********************************************************************************
** Form generated from reading UI file 'jogo.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOGO_H
#define UI_JOGO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_jogo
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *jogo)
    {
        if (jogo->objectName().isEmpty())
            jogo->setObjectName(QStringLiteral("jogo"));
        jogo->resize(400, 300);
        menuBar = new QMenuBar(jogo);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        jogo->setMenuBar(menuBar);
        mainToolBar = new QToolBar(jogo);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        jogo->addToolBar(mainToolBar);
        centralWidget = new QWidget(jogo);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        jogo->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(jogo);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        jogo->setStatusBar(statusBar);

        retranslateUi(jogo);

        QMetaObject::connectSlotsByName(jogo);
    } // setupUi

    void retranslateUi(QMainWindow *jogo)
    {
        jogo->setWindowTitle(QApplication::translate("jogo", "jogo", 0));
    } // retranslateUi

};

namespace Ui {
    class jogo: public Ui_jogo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOGO_H
