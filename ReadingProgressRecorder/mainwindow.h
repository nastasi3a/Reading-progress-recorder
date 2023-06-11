#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QProgressBar>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QValidator>
#include <QMessageBox>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget* tabContentWidget;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //deklaracja metod
    void aktualizujPostep();
    void addBook(QString tytul, QString autor, QString strony, QString currentP);

private slots:

    void on_addBook_clicked();

    void on_deleteBook_clicked();

    void filterLineEditInput(const QString& text);

    void filterSrednik(const QString& text);

    void on_save_clicked();

private:
    QWidget* cloneTabContentWidget(QWidget* sourceWidget);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
