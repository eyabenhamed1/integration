/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QDateEdit *dateEdit;
    QTableView *tableView;
    QLabel *label_7;
    QLineEdit *lineEdit_6;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QLineEdit *lineEdit_7;
    QTableView *tableView_2;
    QLabel *label_9;
    QPushButton *pushButton_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1190, 719);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(140, 300, 191, 41));
        pushButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #002afe;   /* Couleur de fond */\n"
"    border: none;                /* Pas de bordure */\n"
"    color: white;                /* Couleur du texte */\n"
"    padding: 10px 20px;          /* Espacement interne */\n"
"    font-size: 16px;             /* Taille de la police */\n"
"    font-weight: bold;           /* Texte en gras */\n"
"    border-radius: 5px;          /* Bords arrondis */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #45a049;   /* Couleur de fond au survol */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #3e8e41;   /* Couleur de fond quand le bouton est press\303\251 */\n"
"}\n"
""));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(120, 70, 47, 14));
        label->setStyleSheet(QString::fromUtf8("color: black;  \n"
"font: 9pt \"Sitka Subheading\";\n"
"font: 700 9pt \"Segoe UI\";"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(120, 110, 47, 14));
        label_2->setStyleSheet(QString::fromUtf8("color: black;  \n"
"font: 9pt \"Sitka Subheading\";\n"
"font: 700 9pt \"Segoe UI\";"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(120, 140, 47, 14));
        label_3->setStyleSheet(QString::fromUtf8("color: black;  \n"
"font: 9pt \"Sitka Subheading\";\n"
"font: 700 9pt \"Segoe UI\";"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(80, 170, 131, 20));
        label_4->setStyleSheet(QString::fromUtf8("color: black;  \n"
"font: 9pt \"Sitka Subheading\";\n"
"font: 700 9pt \"Segoe UI\";"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(100, 200, 101, 20));
        label_5->setStyleSheet(QString::fromUtf8("color: black;  \n"
"font: 9pt \"Sitka Subheading\";\n"
"font: 700 9pt \"Segoe UI\";"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(120, 230, 47, 14));
        label_6->setStyleSheet(QString::fromUtf8("color: black;  \n"
"font: 9pt \"Sitka Subheading\";\n"
"font: 700 9pt \"Segoe UI\";"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(200, 70, 113, 20));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(200, 110, 113, 20));
        lineEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(200, 140, 113, 20));
        lineEdit_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        lineEdit_4 = new QLineEdit(centralwidget);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(200, 200, 113, 20));
        lineEdit_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-color: rgb(255, 218, 106);\n"
""));
        lineEdit_5 = new QLineEdit(centralwidget);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(200, 230, 113, 20));
        lineEdit_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"\n"
""));
        dateEdit = new QDateEdit(centralwidget);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(200, 170, 121, 22));
        dateEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(390, 120, 441, 221));
        tableView->setStyleSheet(QString::fromUtf8("background-color: rgb(250, 128, 178);\n"
""));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(90, 30, 131, 31));
        label_7->setStyleSheet(QString::fromUtf8("color: black;  \n"
"font: 9pt \"Sitka Subheading\";\n"
"font: 700 9pt \"Segoe UI\";"));
        lineEdit_6 = new QLineEdit(centralwidget);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setGeometry(QRect(200, 40, 113, 20));
        lineEdit_6->setStyleSheet(QString::fromUtf8("background-color: rgb(73, 85, 255);\n"
"background-color: rgb(255, 255, 255);\n"
""));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(390, 60, 101, 41));
        pushButton_2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #002afe;   /* Couleur de fond */\n"
"    border: none;                /* Pas de bordure */\n"
"    color: white;                /* Couleur du texte */\n"
"    padding: 10px 20px;          /* Espacement interne */\n"
"    font-size: 16px;             /* Taille de la police */\n"
"    font-weight: bold;           /* Texte en gras */\n"
"    border-radius: 5px;          /* Bords arrondis */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #45a049;   /* Couleur de fond au survol */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #3e8e41;   /* Couleur de fond quand le bouton est press\303\251 */\n"
"}\n"
""));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(510, 60, 111, 41));
        pushButton_3->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #002afe;   /* Couleur de fond */\n"
"    border: none;                /* Pas de bordure */\n"
"    color: white;                /* Couleur du texte */\n"
"    padding: 10px 20px;          /* Espacement interne */\n"
"    font-size: 16px;             /* Taille de la police */\n"
"    font-weight: bold;           /* Texte en gras */\n"
"    border-radius: 5px;          /* Bords arrondis */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #45a049;   /* Couleur de fond au survol */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #3e8e41;   /* Couleur de fond quand le bouton est press\303\251 */\n"
"}\n"
""));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(900, 190, 151, 41));
        pushButton_4->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #002afe;   /* Couleur de fond */\n"
"    border: none;                /* Pas de bordure */\n"
"    color: white;                /* Couleur du texte */\n"
"    padding: 10px 20px;          /* Espacement interne */\n"
"    font-size: 16px;             /* Taille de la police */\n"
"    font-weight: bold;           /* Texte en gras */\n"
"    border-radius: 5px;          /* Bords arrondis */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #45a049;   /* Couleur de fond au survol */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #3e8e41;   /* Couleur de fond quand le bouton est press\303\251 */\n"
"}\n"
""));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(340, 480, 191, 41));
        pushButton_5->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #002afe;   /* Couleur de fond */\n"
"    border: none;                /* Pas de bordure */\n"
"    color: white;                /* Couleur du texte */\n"
"    padding: 10px 20px;          /* Espacement interne */\n"
"    font-size: 16px;             /* Taille de la police */\n"
"    font-weight: bold;           /* Texte en gras */\n"
"    border-radius: 5px;          /* Bords arrondis */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #45a049;   /* Couleur de fond au survol */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #3e8e41;   /* Couleur de fond quand le bouton est press\303\251 */\n"
"}\n"
""));
        lineEdit_7 = new QLineEdit(centralwidget);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setGeometry(QRect(900, 150, 151, 31));
        tableView_2 = new QTableView(centralwidget);
        tableView_2->setObjectName("tableView_2");
        tableView_2->setGeometry(QRect(550, 360, 491, 241));
        tableView_2->setStyleSheet(QString::fromUtf8("background-color: rgb(250, 128, 178);\n"
""));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(0, 20, 1181, 701));
        label_9->setAutoFillBackground(false);
        label_9->setStyleSheet(QString::fromUtf8("background-image: url('c:/Users/ayadi/Desktop/file.png');\n"
"                     "));
        label_9->setScaledContents(true);
        label_9->setWordWrap(false);
        label_9->setOpenExternalLinks(false);
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(340, 420, 191, 41));
        pushButton_6->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #002afe;   /* Couleur de fond */\n"
"    border: none;                /* Pas de bordure */\n"
"    color: white;                /* Couleur du texte */\n"
"    padding: 10px 20px;          /* Espacement interne */\n"
"    font-size: 16px;             /* Taille de la police */\n"
"    font-weight: bold;           /* Texte en gras */\n"
"    border-radius: 5px;          /* Bords arrondis */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #45a049;   /* Couleur de fond au survol */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #3e8e41;   /* Couleur de fond quand le bouton est press\303\251 */\n"
"}\n"
""));
        MainWindow->setCentralWidget(centralwidget);
        label_9->raise();
        pushButton->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();
        label_6->raise();
        lineEdit->raise();
        lineEdit_2->raise();
        lineEdit_3->raise();
        lineEdit_4->raise();
        lineEdit_5->raise();
        dateEdit->raise();
        tableView->raise();
        label_7->raise();
        lineEdit_6->raise();
        pushButton_2->raise();
        pushButton_3->raise();
        pushButton_4->raise();
        pushButton_5->raise();
        lineEdit_7->raise();
        tableView_2->raise();
        pushButton_6->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1190, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "ajouter", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Etat", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Date_acquisition", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Emplacement", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Prix", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "ID_Equiepent", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "update", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "delete", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "tri", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "stat", nullptr));
        lineEdit_7->setText(QString());
        label_9->setText(QString());
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "exporter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
