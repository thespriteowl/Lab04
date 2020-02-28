#include "httpmanager.h"
#include <QJsonDocument>
#include <QJsonObject>

HTTPManager::HTTPManager(QObject *parent) :
    QObject(parent),
    imageDownloadManager(new QNetworkAccessManager),
    weatherAPIManager(new QNetworkAccessManager)
{
   connect(imageDownloadManager, SIGNAL(finished(QNetworkReply*)),
           this, SLOT(ImageDownloadedHandler(QNetworkReply*)));

   connect(weatherAPIManager, SIGNAL(finished(QNetworkReply*)),
           this, SLOT(WeatherDownloadedHandler(QNetworkReply*)));
}

HTTPManager::~HTTPManager()
{
    delete imageDownloadManager;
    delete weatherAPIManager;
}

void HTTPManager::sendImageRequest()
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://homepages.cae.wisc.edu/~ece533/images/airplane"));
    imageDownloadManager->get(request);
    qDebug() << "Image request sent to address " << request.url();
}

void HTTPManager::sendWeatherRequest(QString zip)
{
    QNetworkRequest request;

    QString address = "http://api.openweathermap.org/data/2.5/weather?zip=" +
            zip + ",us&units=imperial&appid=edade5dd99f63d1ba81f1b671ff5534f";

    request.setUrl(QUrl(address));
    weatherAPIManager->get(request);
    qDebug() << "Weather request sent to address " << request.url();
}

void HTTPManager::ImageDownloadedHandler(QNetworkReply *reply)
{
    qDebug() << "Image reply has arrived!";
    if (reply->error())
    {
        qDebug() << reply->errorString();
        return;
    }

    qDebug() << "Download was successful";
    QPixmap *image = new QPixmap();
    image->loadFromData(reply->readAll());
    reply->deleteLater();

    emit ImageReady(image);
}

void HTTPManager::WeatherDownloadedHandler(QNetworkReply *reply)
{
    qDebug() << "Weather reply has arrived!";
    if (reply->error())
    {
        qDebug() << reply->errorString();
        return;
    }

    qDebug() << "Weather download was successful";

    QString answer = reply->readAll();
    reply->deleteLater();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());
    QJsonObject *jsonObj = new QJsonObject(jsonResponse.object());

    emit WeatherJsonReady(jsonObj);
}
