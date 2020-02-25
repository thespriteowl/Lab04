#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "todolist.h"

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QTimeZone>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setCurrentTime();

    void on_actionImport_To_Do_List_triggered();

    void on_actionTerminate_triggered();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    todolist *myModel;

};
#endif // MAINWINDOW_H
