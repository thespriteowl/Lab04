#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QTimeZone>

#include "todolist.h"
#include "httpmanager.h"

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

    void processImage(QPixmap*);
    void processWeatherJson(QJsonObject *json);

    void on_loadImageButton_clicked();

    void on_weatherDownloadButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    todolist *myModel;
    HTTPManager *httpManager;

};
#endif // MAINWINDOW_H
