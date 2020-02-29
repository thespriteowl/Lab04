#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <iostream>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QInputDialog>

QString zipCode = "98404";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer),
    weatherTimer(new QTimer),
    myModel(new todolist(this)),
    httpManager(new HTTPManager)

{
    ui->setupUi(this);
    ui->todoTable->setModel(myModel);
    ui->todoTable->horizontalHeader()->setStretchLastSection(true);

    //Timers
    connect(timer, SIGNAL(timeout()),
            this, SLOT(setCurrentTime()));
    connect(weatherTimer, SIGNAL(timeout()),
            this, SLOT(updateWeather()));

    setCurrentTime();
    timer->start(1000);

    connect(httpManager, SIGNAL(ImageReady(QPixmap*)),
            this, SLOT(processImage(QPixmap*)));

    connect(httpManager, SIGNAL(WeatherJsonReady(QJsonObject*)),
            this, SLOT(processWeatherJson(QJsonObject*)));

    //Get Network Requests
    httpManager->sendWeatherRequest(zipCode);
    weatherTimer->start(60000); //One minute

    //Graphics Settings
    setStyleSheet("background-color: rgb(0,170,170)");

    ui->weatherDescLabel->setWordWrap(true);
}
MainWindow::~MainWindow()
{
    delete ui;
}

//Updating the Clock
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

    if (timeDay < 5)
        ui->greetingLabel->setText("What are you doing up?!");
    if (timeDay > 4 && timeDay < 12)
        ui->greetingLabel->setText("Good Morning!");
    else if (timeDay > 11 && timeDay < 17)
        ui->greetingLabel->setText("Good Afternoon!");
    else if (timeDay > 16)
        ui->greetingLabel->setText("Good Evening!");
    else
        ui->greetingLabel->setText("Hello, Ragamuffin!");

}

//Update the Weather
void MainWindow::updateWeather()
{
    httpManager->sendWeatherRequest(zipCode);
}

//Menu Bar Actions
void MainWindow::on_actionImport_To_Do_List_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Todo List"), "",
        tr("Todo List (*.csv);;All Files (*)"));

    myModel->openFile(fileName);
}
void MainWindow::on_actionTerminate_triggered()
{
    QApplication::quit();

}

//Process Network Requests
void MainWindow::processImage(QPixmap *image)
{
    ui->weatherIconLabel->setPixmap(*image);
}
void MainWindow::processWeatherJson(QJsonObject *json)
{
    QString weather = json->value("weather").toArray()[0].toObject()["main"].toString();
    double temp = json->value("main").toObject()["temp"].toDouble();
    double humidity = json->value("main").toObject()["humidity"].toDouble();

    QString description = json->value("weather").toArray()[0].toObject()["description"].toString();
    QString location = json->value("name").toString();
    description = "The weather in " + location + " is " + description + ".";

    QString icon = json->value("weather").toArray()[0].toObject()["icon"].toString();
    QString iconUrl = "http://openweathermap.org/img/wn/" +
            icon + ".png";

    { //Json Structure Reference
        /*{
  "coord": {"lon": -122.08,"lat": 37.39},
  "weather": [
    {
      "id": 800,
      "main": "Clear",
      "description": "clear sky",
      "icon": "01d"
    }
  ],
  "base": "stations",
  "main": {
    "temp": 282.55,
    "feels_like": 281.86,
    "temp_min": 280.37,
    "temp_max": 284.26,
    "pressure": 1023,
    "humidity": 100
  },
  "visibility": 16093,
  "wind": {
    "speed": 1.5,
    "deg": 350
  },
  "clouds": {
    "all": 1
  },
  "dt": 1560350645,
  "sys": {
    "type": 1,
    "id": 5122,
    "message": 0.0139,
    "country": "US",
    "sunrise": 1560343627,
    "sunset": 1560396563
  },
  "timezone": -25200,
  "id": 420006353,
  "name": "Mountain View",
  "cod": 200
}*/
    }

    qDebug() << "Json finished, sent Image Request.";
    httpManager->sendImageRequest(iconUrl);

    ui->weatherTempLabel->setText(QString::number(temp) + " F");
    ui->weatherDescLabel->setText(description);
    ui->weatherHumidLabel->setText(QString::number(humidity) + "% Humidity.");

}

void MainWindow::on_actionSelect_Zip_Code_triggered()
{
    zipCode = QInputDialog::getText(this, tr("Type in a new zip code."),
                                    tr("Zip Code: "), QLineEdit::Normal,
                                    zipCode);
    httpManager->sendWeatherRequest(zipCode);
}

void MainWindow::on_actionUpdate_Weather_triggered()
{
    httpManager->sendWeatherRequest(zipCode);
}
