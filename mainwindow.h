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
    void updateWeather();
    void updatePhoto();

    //Network Actions
    void processImage(QPixmap*);
    void processWeatherJson(QJsonObject *json);

    //Menu Actions
    void on_actionImport_To_Do_List_triggered();
    void on_actionTerminate_triggered();
    void on_actionSelect_Zip_Code_triggered();
    void on_actionUpdate_Weather_triggered();

    void on_actionAdd_From_Computer_triggered();

    void on_actionUpload_Photo_triggered();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *weatherTimer;
    QTimer *photoTimer;
    todolist *myModel;
    HTTPManager *httpManager;

};
#endif // MAINWINDOW_H
