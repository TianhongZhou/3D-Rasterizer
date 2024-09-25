/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad_Scene;
    QAction *actionSave_Image;
    QAction *actionEquilateral_Triangle;
    QAction *actionQuit_Esc;
    QAction *actionNone;
    QAction *actionLambertian;
    QAction *actionBlinn_Phong;
    QAction *actionIridescent;
    QAction *actionLit_Sphere;
    QAction *actionToon1;
    QAction *actionToon2;
    QAction *actionLine;
    QWidget *centralWidget;
    QGraphicsView *scene_display;
    QSpinBox *spinBox;
    QLabel *label;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuScenes;
    QMenu *menuReflection;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(697, 612);
        actionLoad_Scene = new QAction(MainWindow);
        actionLoad_Scene->setObjectName(QString::fromUtf8("actionLoad_Scene"));
        actionSave_Image = new QAction(MainWindow);
        actionSave_Image->setObjectName(QString::fromUtf8("actionSave_Image"));
        actionEquilateral_Triangle = new QAction(MainWindow);
        actionEquilateral_Triangle->setObjectName(QString::fromUtf8("actionEquilateral_Triangle"));
        actionQuit_Esc = new QAction(MainWindow);
        actionQuit_Esc->setObjectName(QString::fromUtf8("actionQuit_Esc"));
        actionNone = new QAction(MainWindow);
        actionNone->setObjectName(QString::fromUtf8("actionNone"));
        actionLambertian = new QAction(MainWindow);
        actionLambertian->setObjectName(QString::fromUtf8("actionLambertian"));
        actionBlinn_Phong = new QAction(MainWindow);
        actionBlinn_Phong->setObjectName(QString::fromUtf8("actionBlinn_Phong"));
        actionIridescent = new QAction(MainWindow);
        actionIridescent->setObjectName(QString::fromUtf8("actionIridescent"));
        actionLit_Sphere = new QAction(MainWindow);
        actionLit_Sphere->setObjectName(QString::fromUtf8("actionLit_Sphere"));
        actionToon1 = new QAction(MainWindow);
        actionToon1->setObjectName(QString::fromUtf8("actionToon1"));
        actionToon2 = new QAction(MainWindow);
        actionToon2->setObjectName(QString::fromUtf8("actionToon2"));
        actionLine = new QAction(MainWindow);
        actionLine->setObjectName(QString::fromUtf8("actionLine"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        scene_display = new QGraphicsView(centralWidget);
        scene_display->setObjectName(QString::fromUtf8("scene_display"));
        scene_display->setEnabled(false);
        scene_display->setGeometry(QRect(50, 25, 512, 512));
        scene_display->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scene_display->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scene_display->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
        scene_display->setInteractive(false);
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(580, 90, 42, 22));
        spinBox->setMinimum(1);
        spinBox->setMaximum(16);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(570, 70, 91, 16));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 697, 17));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuScenes = new QMenu(menuBar);
        menuScenes->setObjectName(QString::fromUtf8("menuScenes"));
        menuReflection = new QMenu(menuBar);
        menuReflection->setObjectName(QString::fromUtf8("menuReflection"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuScenes->menuAction());
        menuBar->addAction(menuReflection->menuAction());
        menuFile->addAction(actionLoad_Scene);
        menuFile->addAction(actionSave_Image);
        menuFile->addAction(actionQuit_Esc);
        menuScenes->addAction(actionLine);
        menuReflection->addAction(actionNone);
        menuReflection->addAction(actionLambertian);
        menuReflection->addAction(actionBlinn_Phong);
        menuReflection->addAction(actionIridescent);
        menuReflection->addAction(actionToon1);
        menuReflection->addAction(actionToon2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionLoad_Scene->setText(QCoreApplication::translate("MainWindow", "Load Scene (Ctrl+O)", nullptr));
#if QT_CONFIG(shortcut)
        actionLoad_Scene->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_Image->setText(QCoreApplication::translate("MainWindow", "Save Image (Ctrl+S)", nullptr));
#if QT_CONFIG(shortcut)
        actionSave_Image->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionEquilateral_Triangle->setText(QCoreApplication::translate("MainWindow", "Equilateral Triangle", nullptr));
        actionQuit_Esc->setText(QCoreApplication::translate("MainWindow", "Quit (Esc)", nullptr));
        actionNone->setText(QCoreApplication::translate("MainWindow", "None", nullptr));
        actionLambertian->setText(QCoreApplication::translate("MainWindow", "Lambertian", nullptr));
        actionBlinn_Phong->setText(QCoreApplication::translate("MainWindow", "Blinn-Phong", nullptr));
        actionIridescent->setText(QCoreApplication::translate("MainWindow", "Iridescent", nullptr));
        actionLit_Sphere->setText(QCoreApplication::translate("MainWindow", "Lit Sphere", nullptr));
        actionToon1->setText(QCoreApplication::translate("MainWindow", "Toon1", nullptr));
        actionToon2->setText(QCoreApplication::translate("MainWindow", "Toon2", nullptr));
        actionLine->setText(QCoreApplication::translate("MainWindow", "Line", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Anti-alilasing", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuScenes->setTitle(QCoreApplication::translate("MainWindow", "Scenes", nullptr));
        menuReflection->setTitle(QCoreApplication::translate("MainWindow", "Reflection", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
