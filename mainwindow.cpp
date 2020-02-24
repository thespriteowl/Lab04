#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer)
{
    ui->setupUi(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(setCurrentTime()));

    setCurrentTime();
    timer->start(1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrentTime()
{
    QTime time = QTime::currentTime();
    QString hour = time.toString("hh");
    QString minute = time.toString("mm");
    QString second = time.toString("ss");

    ui->hourLCD->display(hour);
    ui->minuteLCD->display(minute);
    ui->secondLCD->display(second);

    int worldHour = hour.toInt() + 3;

    ui->worldHourLCD->display(worldHour);
    ui->worldMinuteLCD->display(minute);
    ui->worldSecondLCD->display(second);

    int timeDay = hour.toInt();

    if (timeDay >= 0 && timeDay < 12)
        ui->greetingLabel->setText("Good Morning!");
    else if (timeDay > 11 && timeDay < 17)
        ui->greetingLabel->setText("Good Afternoon!");
    else if (timeDay > 16)
        ui->greetingLabel->setText("Good Evening!");
    else
        ui->greetingLabel->setText("Hello!");

}



