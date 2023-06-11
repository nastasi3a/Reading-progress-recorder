/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *widget;
    QLineEdit *title;
    QLabel *Ltitle;
    QLineEdit *author;
    QLabel *Lauthor;
    QLabel *Lpages;
    QLineEdit *pages;
    QPushButton *addBook;
    QPushButton *deleteBook;
    QTabWidget *booksTab;
    QPushButton *save;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(670, 324);
        QFont font;
        font.setFamilies({QString::fromUtf8("Bookman Old Style")});
        font.setPointSize(10);
        MainWindow->setFont(font);
        MainWindow->setLocale(QLocale(QLocale::Polish, QLocale::Poland));
        widget = new QWidget(MainWindow);
        widget->setObjectName("widget");
        title = new QLineEdit(widget);
        title->setObjectName("title");
        title->setGeometry(QRect(10, 50, 271, 30));
        Ltitle = new QLabel(widget);
        Ltitle->setObjectName("Ltitle");
        Ltitle->setGeometry(QRect(10, 20, 68, 22));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Bookman Old Style")});
        font1.setPointSize(12);
        Ltitle->setFont(font1);
        author = new QLineEdit(widget);
        author->setObjectName("author");
        author->setGeometry(QRect(10, 120, 271, 30));
        Lauthor = new QLabel(widget);
        Lauthor->setObjectName("Lauthor");
        Lauthor->setGeometry(QRect(10, 90, 71, 22));
        Lauthor->setFont(font1);
        Lpages = new QLabel(widget);
        Lpages->setObjectName("Lpages");
        Lpages->setGeometry(QRect(10, 160, 121, 22));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Bookman Old Style")});
        font2.setPointSize(12);
        font2.setKerning(true);
        Lpages->setFont(font2);
        pages = new QLineEdit(widget);
        pages->setObjectName("pages");
        pages->setGeometry(QRect(10, 190, 271, 30));
        pages->setAcceptDrops(true);
        addBook = new QPushButton(widget);
        addBook->setObjectName("addBook");
        addBook->setGeometry(QRect(10, 250, 90, 31));
        deleteBook = new QPushButton(widget);
        deleteBook->setObjectName("deleteBook");
        deleteBook->setGeometry(QRect(190, 250, 90, 31));
        booksTab = new QTabWidget(widget);
        booksTab->setObjectName("booksTab");
        booksTab->setGeometry(QRect(300, 0, 371, 361));
        save = new QPushButton(widget);
        save->setObjectName("save");
        save->setGeometry(QRect(100, 250, 90, 31));
        MainWindow->setCentralWidget(widget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 670, 24));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        booksTab->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        title->setText(QString());
        Ltitle->setText(QCoreApplication::translate("MainWindow", "Tytul", nullptr));
        author->setText(QString());
        Lauthor->setText(QCoreApplication::translate("MainWindow", "Autor", nullptr));
        Lpages->setText(QCoreApplication::translate("MainWindow", "Ilosc stron", nullptr));
        pages->setText(QString());
        addBook->setText(QCoreApplication::translate("MainWindow", "Dodaj", nullptr));
        deleteBook->setText(QCoreApplication::translate("MainWindow", "Usun", nullptr));
        save->setText(QCoreApplication::translate("MainWindow", "Zapisz", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
