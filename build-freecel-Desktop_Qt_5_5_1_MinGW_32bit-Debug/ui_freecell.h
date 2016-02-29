/********************************************************************************
** Form generated from reading UI file 'freecell.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FREECELL_H
#define UI_FREECELL_H

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

class Ui_freecell
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *freecell)
    {
        if (freecell->objectName().isEmpty())
            freecell->setObjectName(QStringLiteral("freecell"));
        freecell->resize(400, 300);
        menuBar = new QMenuBar(freecell);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        freecell->setMenuBar(menuBar);
        mainToolBar = new QToolBar(freecell);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        freecell->addToolBar(mainToolBar);
        centralWidget = new QWidget(freecell);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        freecell->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(freecell);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        freecell->setStatusBar(statusBar);

        retranslateUi(freecell);

        QMetaObject::connectSlotsByName(freecell);
    } // setupUi

    void retranslateUi(QMainWindow *freecell)
    {
        freecell->setWindowTitle(QApplication::translate("freecell", "freecell", 0));
    } // retranslateUi

};

namespace Ui {
    class freecell: public Ui_freecell {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FREECELL_H
